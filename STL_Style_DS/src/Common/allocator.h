#ifndef __CUSTOM_ALLOCATOR_H__
#define __CUSTOM_ALLOCATOR_H__

#include "Common/logger.h"

namespace ns_Util
{
#define DISABLE_17_DEPRICATED_WARNINGS 1

#define NO_DISCARD  [[nodiscard]]
#define NO_RETURN   [[noreturn]]

#define CXX17_DEPRECATE _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS

#define RESUME_DEPRICATED_WARNING   _STL_RESTORE_DEPRECATED_WARNING
#define PAUSE_DEPRICATED_WARNING    _STL_DISABLE_DEPRECATED_WARNING
#define DEFAULT_NEW_ALIGNMENT       __STDCPP_DEFAULT_NEW_ALIGNMENT__

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define WINDOWS_PLATFORM
    #define DECLSPEC(x) __declspec(x)
#else   // defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define DECLSPEC(x)
#endif  // defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)

#define ENABLE_CXX_20 1
#ifdef __cpp_lib_constexpr_dynamic_alloc
    #define CXX_20_DYNAMIC_ALLOC
#endif  // __cpp_lib_constexpr_dynamic_alloc

#if _HAS_CXX17
    #define INLINE_VAR inline
    #define INLINE_OR_CONSTEXPR constexpr
#else // _HAS_CXX17
    #define INLINE_VAR
    #define INLINE_OR_CONSTEXPR inline
#endif // _HAS_CXX17

#define NODISCARD_CONSTEXPR NO_DISCARD INLINE_OR_CONSTEXPR

template<typename DataType>
class EasyAllocator
{
public:
    NODISCARD_CONSTEXPR DataType* allocate(const size_t size)
	{
		return traits_t::allocate(m_allocator, size);
	}

	template<typename... Args>
    NODISCARD_CONSTEXPR void construct(DataType* const ptr, Args&&... _Args)
	{
		traits_t::construct(m_allocator, ptr, std::forward<Args>(_Args)...);
	}

    INLINE_OR_CONSTEXPR void destroy(DataType* const ptr)
	{
		traits_t::destroy(m_allocator, ptr);
	}

    INLINE_OR_CONSTEXPR void deallocate(DataType* const ptr, const size_t size)
	{
		traits_t::deallocate(m_allocator, ptr, size);
	}
private:
	std::allocator<DataType>	m_allocator{};
	using traits_t = std::allocator_traits<decltype(m_allocator)>;
};



// Tidy_guard
template <typename T>
struct NO_DISCARD Tidy_guard   // class with destructor that calls Tidy
{
    T* Target;
    ~Tidy_guard()
    {
        if (Target)
        {
            Target->Tidy();
        }
    }
};

// Tidy_deallocate_guard
template <typename T>
struct NO_DISCARD Tidy_deallocate_guard     // class with destructor that calls Tidy_deallocate
 {
    T* Target;
    ~Tidy_deallocate_guard()
    {
        if (Target)
        {
            Target->Tidy_deallocate();
        }
    }
};

// Nothrow_compare
template <typename Keycmp, typename Lhs, typename Rhs>
INLINE_VAR INLINE_OR_CONSTEXPR bool Nothrow_compare = noexcept(
    static_cast<bool>(std::declval<const Keycmp&>()(std::declval<const Lhs&>(), std::declval<const Rhs&>())));


// Default_allocate_traits
struct Default_allocate_traits
{
    DECLSPEC(allocator) static
#ifdef __clang__ // Clang and MSVC implement P0784R7 differently; see GH-1532
    INLINE_OR_CONSTEXPR
#endif // __clang__
    void* Allocate(const size_t byteCount)
    {
        return ::operator new(byteCount);
    }

#ifdef __cpp_aligned_new
    DECLSPEC(allocator) static
#ifdef __clang__ // Clang and MSVC implement P0784R7 differently; see GH-1532
    INLINE_OR_CONSTEXPR
#endif // __clang__
    void* Allocate_aligned(const size_t byteCount, const size_t alignment)
    {
#ifdef __clang__ // Clang and MSVC implement P0784R7 differently; see GH-1532
#ifdef __cpp_lib_constexpr_dynamic_alloc
        if (Is_constant_evaluated())
        {
            return ::operator new(byteCount);
        }
        else
#endif // __cpp_lib_constexpr_dynamic_alloc
#endif // __clang__
        {
            return ::operator new (byteCount, std::align_val_t{ alignment });
        }
    }
#endif // __cpp_aligned_new
};


// Is_pow_2
INLINE_OR_CONSTEXPR bool Is_pow_2(const size_t value) noexcept
{
    return value != 0 && (value & (value - 1)) == 0;
}

// VAR kBig_allocation_threshold
INLINE_OR_CONSTEXPR size_t kBig_allocation_threshold = 4096;

// VAR kBig_allocation_alignment
INLINE_OR_CONSTEXPR size_t kBig_allocation_alignment = 32;


static_assert(2 * sizeof(void*) <= kBig_allocation_alignment, "Big allocation alignment should at least match vector register alignment");
static_assert(Is_pow_2(kBig_allocation_alignment), "Big allocation alignment must be a power of two");


// VAR kNon_user_size
#ifdef _DEBUG
    INLINE_OR_CONSTEXPR size_t kNon_user_size = 2 * sizeof(void*) + kBig_allocation_alignment - 1;
#else   // _DEBUG
    INLINE_OR_CONSTEXPR size_t kNon_user_size = sizeof(void*) + kBig_allocation_alignment - 1;
#endif  // _DEBUG


// VAR kBig_allocation_sentinel
#ifdef _WIN64
    INLINE_OR_CONSTEXPR size_t kBig_allocation_sentinel = 0xFAFAFAFAFAFAFAFAULL;
#else   // _WIN64
    INLINE_OR_CONSTEXPR size_t kBig_allocation_sentinel = 0xFAFAFAFAUL;
#endif  // _WIN64



// Allocate_manually_vector_aligned
template <typename Traits>
DECLSPEC(allocator) void* Allocate_manually_vector_aligned(const size_t byteCount)
{
    // allocate byteCount manually aligned to at least Big_allocation_alignment
    const size_t block_size = kNon_user_size + byteCount;
    if (block_size <= byteCount)
    {
        throw std::bad_array_new_length{};
    }

    const uintptr_t ptr_container = reinterpret_cast<uintptr_t>(Traits::Allocate(block_size));

    _STL_VERIFY(ptr_container != 0, "invalid argument"); // validate even in release since we're doing p[-1]
    
    void* const ptr = reinterpret_cast<void*>((ptr_container + kNon_user_size) & ~(kBig_allocation_alignment - 1));
    static_cast<uintptr_t*>(ptr)[-1] = ptr_container;

#ifdef _DEBUG
    static_cast<uintptr_t*>(ptr)[-2] = kBig_allocation_sentinel;
#endif  // _DEBUG
    return ptr;
}


// Adjust_manually_vector_aligned
inline void Adjust_manually_vector_aligned(void*& ptr, size_t& byteCount)
{
    // adjust parameters from _Allocate_manually_vector_aligned to pass to operator delete
    byteCount += kNon_user_size;

    const uintptr_t* const ptr_user = reinterpret_cast<uintptr_t*>(ptr);
    const uintptr_t ptr_container = ptr_user[-1];

    // If the following asserts, it likely means that we are performing
    // an aligned delete on memory coming from an unaligned allocation.
    _STL_ASSERT(ptr_user[-2] == kBig_allocation_sentinel, "invalid argument");

    // Extra paranoia on aligned allocation/deallocation; ensure _Ptr_container is
    // in range [_Min_back_shift, _Non_user_size]
#ifdef _DEBUG
    constexpr uintptr_t min_back_shift = 2 * sizeof(void*);
#else   // _DEBUG
    constexpr uintptr_t min_back_shift = sizeof(void*);
#endif  // _DEBUG
    const uintptr_t back_shift = reinterpret_cast<uintptr_t>(ptr) - ptr_container;

    _STL_VERIFY(back_shift >= min_back_shift && back_shift <= kNon_user_size, "invalid argument");

    ptr = reinterpret_cast<void*>(ptr_container);
}


// Allocate
#ifdef __cpp_aligned_new
template <size_t alignment, typename Traits = Default_allocate_traits, std::enable_if_t<(alignment > DEFAULT_NEW_ALIGNMENT), int> = 0>
DECLSPEC(allocator) INLINE_OR_CONSTEXPR void* Allocate(const size_t byteCount)
{
    // allocate bytes when __cpp_aligned_new && Align > __STDCPP_DEFAULT_NEW_ALIGNMENT__
    if (byteCount == 0)
    {
        return nullptr;
    }

#ifdef CXX_20_DYNAMIC_ALLOC
    if (Is_constant_evaluated()) {
        return Traits::Allocate(byteCount);
    }
    else
#endif  // CXX_20_DYNAMIC_ALLOC
    {
        size_t passed_align = alignment;
#if defined(_M_IX86) || defined(_M_X64)
        if (byteCount >= kBig_allocation_threshold)
        {
            // boost the alignment of big allocations to help autovectorization
            passed_align = std::max(alignment, kBig_allocation_alignment);
        }
#endif  // defined(_M_IX86) || defined(_M_X64)
        return Traits::Allocate_aligned(byteCount, passed_align);
    }
}


// Deallocate
template <size_t alignment, std::enable_if_t<(alignment > DEFAULT_NEW_ALIGNMENT), int> = 0>
INLINE_OR_CONSTEXPR void Deallocate(void *ptr, const size_t byteCount) noexcept
{
    // deallocate storage allocated by _Allocate when __cpp_aligned_new && _Align > __STDCPP_DEFAULT_NEW_ALIGNMENT__
#ifdef CXX_20_DYNAMIC_ALLOC
    if (Is_constant_evaluated())
    {
        ::operator delete(ptr);
    }
    else
#endif  // CXX_20_DYNAMIC_ALLOC
    {
        size_t passed_align = alignment;
#if defined(_M_IX86) || defined(_M_X64)
        if (byteCount >= kBig_allocation_threshold)      // boost the alignment of big allocations to help autovectorization
        { 
            passed_align = std::max(alignment, kBig_allocation_alignment);
        }
#endif  // defined(_M_IX86) || defined(_M_X64)
        ::operator delete (ptr, byteCount, std::align_val_t{passed_align});
    }
}

#define HAS_ALIGNED_NEW 1
#else   // __cpp_aligned_new
#define HAS_ALIGNED_NEW 0
#endif  // __cpp_aligned_new


// Allocate
template <size_t alignment, typename Traits = Default_allocate_traits,
    std::enable_if_t<(!HAS_ALIGNED_NEW || alignment <= DEFAULT_NEW_ALIGNMENT), int> = 0>
DECLSPEC(allocator) INLINE_OR_CONSTEXPR void* Allocate(const size_t byteCount)
{
    // allocate byteCount when !HAS_ALIGNED_NEW || Align <= __STDCPP_DEFAULT_NEW_ALIGNMENT__
#if defined(_M_IX86) || defined(_M_X64)
#ifdef CXX_20_DYNAMIC_ALLOC 
    if (!Is_constant_evaluated())
#endif // CXX_20_DYNAMIC_ALLOC
    {
        if (byteCount >= kBig_allocation_threshold)  // boost the alignment of big allocations to help autovectorization
        {
            return Allocate_manually_vector_aligned<Traits>(byteCount);
        }
    }
#endif // defined(_M_IX86) || defined(_M_X64)
    return byteCount ? Traits::Allocate(byteCount) : nullptr;
}


// Deallocate
template <size_t alignment, std::enable_if_t<(!HAS_ALIGNED_NEW || alignment <= DEFAULT_NEW_ALIGNMENT), int> = 0>
INLINE_OR_CONSTEXPR void Deallocate(void *ptr, size_t byteCount) noexcept
{
    // deallocate storage allocated by Allocate when !HAS_ALIGNED_NEW || Align <= __STDCPP_DEFAULT_NEW_ALIGNMENT__
#ifdef CXX_20_DYNAMIC_ALLOC
    if (Is_constant_evaluated())
    {
        ::operator delete(ptr);
    }
    else
#endif // CXX_20_DYNAMIC_ALLOC
    {
#if defined(_M_IX86) || defined(_M_X64)
        if (byteCount >= kBig_allocation_threshold)  // boost the alignment of big allocations to help autovectorization
        {
            Adjust_manually_vector_aligned(ptr, byteCount);
        }
#endif // defined(_M_IX86) || defined(_M_X64)
        ::operator delete(ptr, byteCount);
    }
}


template<typename T>
INLINE_OR_CONSTEXPR size_t NewAlignment = std::max(alignof(T), static_cast<size_t>(DEFAULT_NEW_ALIGNMENT));

template <size_t size_of_T>
NODISCARD_CONSTEXPR size_t GetSizeOfCountNumOfT(const size_t count)
{
    constexpr bool bIsOverflowPossible = size_of_T > 1;
    if constexpr (bIsOverflowPossible)
    {
        constexpr size_t maxSize = std::numeric_limits<size_t>::max() / size_of_T;
        if (count > maxSize)
        {
            throw std::bad_array_new_length();
        }
    }
    return count * size_of_T;
}


// AllocationResult
template<typename Pointer>
struct AllocationResult
{
    Pointer     m_ptr{};
    size_t      m_count{};

    AllocationResult() = default;
    ~AllocationResult() = default;

    AllocationResult(Pointer ptr, size_t count)
        : m_ptr(ptr)
        , m_count(count)
    {}
};

// void_cast_ptr
template<typename T>
NODISCARD_CONSTEXPR void* void_cast_ptr(T ptr) noexcept
{
    if constexpr (std::is_pointer_v<T>)
    {
        return const_cast<void*>(static_cast<const volatile void*>(ptr));
    }
    else
    {
        return const_cast<void*>(static_cast<const volatile void*>(std::addressof(*ptr)));
    }
}


#ifdef DISABLE_17_DEPRICATED_WARNINGS
PAUSE_DEPRICATED_WARNING
#endif  // DISABLE_17_DEPRICATED_WARNINGS

template<typename T>
class CustomAllocator
{
public:
    static_assert(!std::is_const_v<T>, "The C++ Standard forbids containers of const elements "
        "because allocator<const T> is ill-formed.");
    using CustomDefaultAllocator = CustomAllocator;
    using _From_primary = CustomAllocator;

    using value_type = T;
    using pointer               CXX17_DEPRECATE = T*;
    using const_pointer         CXX17_DEPRECATE = const T*;
    using void_pointer = void*;
    using const_void_pointer = const void*;

    using reference = T&;
    using const_reference = const T&;

    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using propagate_on_container_move_assignment = std::true_type;

    template<typename U>
    struct CXX17_DEPRECATE rebind
    {
        using other = typename CustomAllocator<U>;
    };

    using is_always_equal CXX17_DEPRECATE = std::true_type;

public:
    // Ctor & Dtor
    ~CustomAllocator() = default;
    INLINE_OR_CONSTEXPR CustomAllocator() noexcept = default;

    INLINE_OR_CONSTEXPR CustomAllocator(const CustomAllocator& other) noexcept = default;
    INLINE_OR_CONSTEXPR CustomAllocator(CustomAllocator&& other) noexcept = default;

    INLINE_OR_CONSTEXPR CustomAllocator& operator=(const CustomAllocator& other) noexcept = default;
    INLINE_OR_CONSTEXPR CustomAllocator& operator=(CustomAllocator&& other) noexcept = default;

    template<typename U>
    INLINE_OR_CONSTEXPR CustomAllocator(const CustomAllocator<U>& other) noexcept {};

    // Member functions
    CXX17_DEPRECATE NODISCARD_CONSTEXPR pointer address(reference val) const noexcept { return std::addressof(val); }
    CXX17_DEPRECATE NODISCARD_CONSTEXPR const_pointer address(const_reference val) const noexcept { return std::addressof(val); }

    CXX17_DEPRECATE NODISCARD_CONSTEXPR pointer allocate(const size_type count, const void* hint) { return allocate(count); }
    //_CXX17_DEPRECATE _NO_DISCARD T* allocate(std::size_t count) { return nullptr; }
    NODISCARD_CONSTEXPR pointer allocate(const size_type count)
    {
        return static_cast<T*>(Allocate<NewAlignment<T>>(GetSizeOfCountNumOfT<sizeof(T)>(count)));
    }

    NODISCARD_CONSTEXPR AllocationResult<pointer> allocate_at_least(const size_type count) { return AllocationResult(allocate(count), count); }

    INLINE_OR_CONSTEXPR void deallocate(pointer ptr, const size_type count)
    {
        Deallocate<NewAlignment<T>>(ptr, sizeof(T) * count);
    }

    CXX17_DEPRECATE NODISCARD_CONSTEXPR size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);;
    }

    template <typename U, typename... Args>
    CXX17_DEPRECATE INLINE_OR_CONSTEXPR void construct(U* ptr, Args&&... args)
    {
        ::new (void_cast_ptr(ptr)) U(std::forward<Args>(args)...);
    }

    template <typename U>
    INLINE_OR_CONSTEXPR void destroy(U* const ptr)
    {
        ptr->~U();
    }
};

#ifdef DISABLE_17_DEPRICATED_WARNINGS
RESUME_DEPRICATED_WARNING
#endif  // DISABLE_17_DEPRICATED_WARNINGS

template<typename T, typename U>
NODISCARD_CONSTEXPR bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept
{
    return true;
}

template<typename T, typename U>
NODISCARD_CONSTEXPR bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept
{
    return false;
}










/*
template <typename T>
class allocator
{
public:
    using  value_type       = T;
    using  size_type        = size_t;
    using  difference_type  = ptrdiff_t;
    using  pointer          = value_type*;
    using  const_pointer    = const value_type *;
    using  reference        = value_type&;
    using  const_reference  = const value_type&;
    
    allocator();
    allocator(const allocator<T>&);
    ~allocator();

    template <class U> allocator(const allocator<U>&);
    template <class U> struct rebind { typedef allocator<U> other; };

    T* address(T &) const;
    const T* address(const T&) const;
    _NO_DISCARD T* allocate(size_type, const void* = nullptr);
    void deallocate(T *, size_type);
    void construct(T *, const T&);
    void destroy(T *);
    size_type max_size() const;
};

template<typename T, typename U>
inline bool operator==(const allocator<T>&, const allocator<U>&) { return true; }

template<typename T, typename U>
inline bool operator!=(const allocator<T>&, const allocator<U>&) { return false; }

*/
template <typename T>
class my_allocator
{
public:
    using  value_type       = T;
    using  size_type        = size_t;
    using  difference_type  = ptrdiff_t;
    using  pointer          = value_type*;
    using  const_pointer    = const value_type*;
    using  reference        = value_type&;
    using  const_reference  = const value_type&;

    my_allocator() {}
    my_allocator(const my_allocator&) {}

    NODISCARD_CONSTEXPR T* allocate(size_type count, const void *hint = nullptr)
    {
        if (count > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
            throw std::bad_array_new_length();
        }

        if (T *ptr = static_cast<T*>(std::malloc(count * sizeof(T))))
        {
            Logger::LOG_MSG("Used my_allocator to allocate at address = ", ptr, " (+)\n");
            return ptr;
        }
        throw std::bad_alloc();
    }

    INLINE_OR_CONSTEXPR void deallocate(void* ptr, size_type)
    {
        if (ptr)
        {
            Logger::LOG_MSG("Used my_allocator to deallocate at address = ", ptr, " (-)\n");
            free(ptr);
        }
    }

    NODISCARD_CONSTEXPR T* address(T &val) const { return std::addressof(val); }

    NODISCARD_CONSTEXPR const T* address(const T &val) const { return std::addressof(val); }

    NODISCARD_CONSTEXPR my_allocator& operator=(const my_allocator&) { return *this; }

    INLINE_OR_CONSTEXPR void construct(T *ptr, const T& val) { new ((T *)ptr) T(val); }

    INLINE_OR_CONSTEXPR void destroy(T *ptr) const { ptr->~T(); }
    NODISCARD_CONSTEXPR size_type max_size() const { return size_type(-1); }

    template <class U>
    struct rebind { typedef my_allocator<U> other; };

    template <class U>
    INLINE_OR_CONSTEXPR my_allocator(const my_allocator<U>&) {}

    template <class U>
    NODISCARD_CONSTEXPR my_allocator& operator=(const my_allocator<U>&) { return *this; }
};

}

#endif //__CUSTOM_ALLOCATOR_H__