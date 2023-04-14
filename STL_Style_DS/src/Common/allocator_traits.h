#ifndef __CUSTOM_ALLOCATOR_TRAITS_H__
#define __CUSTOM_ALLOCATOR_TRAITS_H__

#include "Common/allocator.h"
#include "Common/logger.h"

namespace ns_Util
{
/***********************************************************************************************************************/
// Example  : https://en.cppreference.com/w/cpp/types/void_t START

// primary template handles types that have no nested ::type member:
template<typename, typename = void >
struct has_type_member : std::false_type { };

// specialization recognizes types that do have a nested ::type member:
template<typename T>
struct has_type_member<T, std::void_t<typename T::type>> : std::true_type { };

// primary template handles types that do not support :: pre-increment member func:
template<typename, typename = void >
struct has_MemberFunc_pre_increment : std::false_type { };
// specialization recognizes types that do support :: pre-increment member func:
template<typename T>
struct has_MemberFunc_pre_increment<T, std::void_t<decltype(++std::declval<T&>())>> : std::true_type { };

// Example  : https://en.cppreference.com/w/cpp/types/void_t END
/***********************************************************************************************************************/


// Is_constant_evaluated
NODISCARD_CONSTEXPR bool Is_constant_evaluated() noexcept
{
    return __builtin_is_constant_evaluated();
}

// Unfancy
template <typename Ptrty>
NODISCARD_CONSTEXPR auto Unfancy(Ptrty ptr) noexcept   // converts from a fancy pointer to a plain pointer
{
    return std::addressof(*ptr);
}

// Unfancy
template<typename T>
NODISCARD_CONSTEXPR T* Unfancy(T* ptr) noexcept        // do nothing for plain pointers
{
    return ptr;
}

// Remove_cvref_t
template <typename T>
using Remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

// Same_impl
template <typename T1, typename T2>
using Same_impl = std::is_same<T1, T2>;

// Is_from_primary
template <typename T>
using Is_from_primary = Same_impl<typename T::_From_primary, T>;

// Same_as
template <typename T1, typename T2>
using Same_as = std::conjunction<Same_impl<T1, T2>, Same_impl<T2, T1>>;

template <typename Iter>
using Iter_cat_t = typename std::iterator_traits<Iter>::iterator_category;

template <typename T, typename = void>
INLINE_VAR constexpr bool Is_iterator_v = false;

template <typename T>
INLINE_VAR constexpr bool Is_iterator_v<T, std::void_t<Iter_cat_t<T>>> = true;


// Get_pointer_type
template<typename T, typename = void>
struct Get_pointer_type
{
    using type = typename T::value_type*;
};

PAUSE_DEPRICATED_WARNING
template<typename T>
struct Get_pointer_type<T, std::void_t<typename T::pointer>>
{
    using type = typename T::pointer;
};
RESUME_DEPRICATED_WARNING

// Get_const_pointer_type
template<typename T, typename = void>
struct Get_const_pointer_type
{
    using type = typename std::pointer_traits<typename Get_pointer_type<T>::type>::template rebind<const typename T::value_type>;
};

PAUSE_DEPRICATED_WARNING
template<typename T>
struct Get_const_pointer_type<T, std::void_t<typename T::const_pointer>>
{
    using type = typename T::const_pointer;
};
RESUME_DEPRICATED_WARNING

// Get_void_pointer_type
template<typename T, typename = void>
struct Get_void_pointer_type
{
    using type = typename std::pointer_traits<typename Get_pointer_type<T>::type>::template rebind<void>;
};

template<typename T>
struct Get_void_pointer_type<T, std::void_t<typename T::void_pointer>>
{
    using type = typename T::void_pointer;
};

// Get_const_void_pointer_type
template<typename T, typename = void>
struct Get_const_void_pointer_type
{
    using type = typename std::pointer_traits<typename Get_pointer_type<T>::type>::template rebind<const void>;
};

template<typename T>
struct Get_const_void_pointer_type<T, std::void_t<typename T::const_void_pointer>>
{
    using type = typename T::const_void_pointer;
};

// Get_difference_type
template<typename T, typename = void>
struct Get_difference_type
{
    using type = std::pointer_traits<typename Get_pointer_type<T>::type>::template difference_type;
};

template<typename T>
struct Get_difference_type<T, std::void_t<typename T::difference_type>>
{
    using type = typename T::difference_type;
};

// Get_size_type
template<typename T, typename = void>
struct Get_size_type
{
    using type = std::make_unsigned_t<typename Get_difference_type<T>::type>;
};

template<typename T>
struct Get_size_type<T, std::void_t<typename T::size_type>>
{
    using type = typename T::size_type;
};

// Get_propagate_on_container_copy_assignment
template<typename, typename = void>
struct Get_propagate_on_container_copy_assignment
{
    using type = std::false_type;
};

template<typename T>
struct Get_propagate_on_container_copy_assignment<T, std::void_t<typename T::propagate_on_container_copy_assignment>>
{
    using type = typename T::propagate_on_container_copy_assignment;
};

// Get_propagate_on_container_move_assignment
template<typename, typename = void>
struct Get_propagate_on_container_move_assignment
{
    using type = std::false_type;
};

template<typename T>
struct Get_propagate_on_container_move_assignment<T, std::void_t<typename T::propagate_on_container_move_assignment>>
{
    using type = typename T::propagate_on_container_move_assignment;
};

// Get_propagate_on_container_swap
template<typename, typename = void>
struct Get_propagate_on_container_swap
{
    using type = std::false_type;
};

template<typename T>
struct Get_propagate_on_container_swap<T, std::void_t<typename T::propagate_on_container_swap>>
{
    using type = typename T::propagate_on_container_swap;
};

// Get_is_always_equal
template<typename T, typename = void>
struct Get_is_always_equal
{
    using type = typename std::is_empty<T>::value;
};

PAUSE_DEPRICATED_WARNING
template<typename T>
struct Get_is_always_equal<T, std::void_t<typename T::is_always_equal>>
{
    using type = typename T::is_always_equal;
};
RESUME_DEPRICATED_WARNING

// Replace_first_parameter
template<typename Newfirst, class T>
struct Replace_first_parameter;

template<typename Newfirst, template <typename, typename...> typename T, typename First, typename... Rest>
struct Replace_first_parameter<Newfirst, T<First, Rest...>>
{
    using type = T<Newfirst, Rest...>;      // given _Ty<_First, _Rest...>, replace _First
};

// Get_rebind_alloc_type
template<typename T, typename U, typename = void>
struct Get_rebind_alloc_type
{
    using type = typename Replace_first_parameter<U, T>::type;
};

PAUSE_DEPRICATED_WARNING
template<typename T, typename U>
struct Get_rebind_alloc_type<T, U, std::void_t<typename T::template rebind<U>::other>>
{
    using type = typename T::template rebind<U>::other;
};
RESUME_DEPRICATED_WARNING

// Has_MemberFunc_max_size
template<typename Alloc, typename = void>
struct Has_MemberFunc_max_size : std::false_type {};

template<typename Alloc>
struct Has_MemberFunc_max_size<Alloc, std::void_t<decltype(std::declval<Alloc&>().max_size())>> : std::true_type {};

// Has_MemberFunc_allocate
template<typename Alloc, typename size_type, typename = void>
struct Has_MemberFunc_allocate : std::false_type {};

template<typename Alloc, typename size_type>
struct Has_MemberFunc_allocate<Alloc, const size_type,
    std::void_t<decltype(std::declval<Alloc&>().allocate(
        std::declval<const size_type&>())
        )>> : std::true_type {};

// Has_MemberFunc_allocate_hint
template<typename Alloc, typename size_type, typename const_void_pointer, typename = void>
struct Has_MemberFunc_allocate_hint : std::false_type {};

template<typename Alloc, typename size_type, typename const_void_pointer>
struct Has_MemberFunc_allocate_hint<Alloc, size_type, const_void_pointer, 
        std::void_t<decltype(std::declval<Alloc&>().allocate(
            std::declval<const size_type&>(), std::declval<const_void_pointer&>())
        )>> : std::true_type {};

// Has_MemberFunc_deallocate
template<typename Alloc, typename pointer, typename size_type, typename = void>
struct Has_MemberFunc_deallocate : std::false_type {};

template<typename Alloc, typename pointer, typename size_type>
struct Has_MemberFunc_deallocate<Alloc, pointer, const size_type,
    std::void_t<decltype(std::declval<Alloc&>().deallocate(
        std::declval<pointer&>(), std::declval<const size_type&>())
        )>> : std::true_type {};


// Has_No_allocator_construct
template<typename void_type, typename... Args>
struct Has_No_allocator_construct : std::true_type {};

template<typename Alloc, typename Ptr, typename... Args>
struct Has_No_allocator_construct<
    std::void_t<decltype(std::declval<Alloc&>().construct(std::declval<Ptr>(), std::declval<Args>()...))>, Alloc, Ptr, Args...> : std::false_type {};

// Has_MemberFunc_select_on_container_copy_construction
template<typename Alloc, typename = void>
struct Has_MemberFunc_select_on_container_copy_construction : std::false_type {};

template<typename Alloc>
struct Has_MemberFunc_select_on_container_copy_construction<Alloc,
    std::void_t<decltype(std::declval<const Alloc&>().select_on_container_copy_construction())>> : std::true_type {};

// Has_no_alloc_destroy
template<typename Alloc, typename Ptr, typename = void>
struct Has_no_alloc_destroy : std::true_type {};

template<typename Alloc, typename Ptr>
struct Has_no_alloc_destroy<Alloc, Ptr, std::void_t<decltype(std::declval<Alloc&>().destroy(std::declval<Ptr>()))>> : std::false_type {};

// Is_default_allocator
template<typename Alloc, typename = void>
struct Is_default_allocator : std::false_type {};

template<typename T>
struct Is_default_allocator<CustomAllocator<T>, std::void_t<typename CustomAllocator<T>::CustomDefaultAllocator>>
    : std::is_same<typename CustomAllocator<T>::CustomDefaultAllocator, CustomAllocator<T>>::type {};

// Uses_default_construct
template<typename Alloc, typename Ptr, typename... Args>
using Uses_default_construct = std::disjunction<Is_default_allocator<Alloc>, Has_No_allocator_construct<void, Alloc, Ptr, Args...>>;

// Uses_default_destroy
template<typename Alloc, typename Ptr>
using Uses_default_destroy = std::disjunction<Is_default_allocator<Alloc>, Has_no_alloc_destroy<Alloc, Ptr>>;


template<typename Alloc>
class CustomAllocator_traits
{
public:
    using allocator_type        = Alloc;
    using value_type            = typename Alloc::value_type;

    //using pointer               = typename Alloc::pointer | typename value_type*;
    using pointer               = typename Get_pointer_type<Alloc>::type;
    using const_pointer         = typename Get_const_pointer_type<Alloc>::type;         //std::pointer_traits<pointer>::rebind<const value_type>
    using void_pointer          = typename Get_void_pointer_type<Alloc>::type;          // void * or Alloc::void_pointer
    using const_void_pointer    = typename Get_const_void_pointer_type<Alloc>::type;    // const void * or Alloc::const_void_pointer
    using difference_type       = typename Get_difference_type<Alloc>::type;            //std::pointer_traits<pointer>::difference_type
    using size_type             = typename Get_size_type<Alloc>::type;                  //std::make_unsigned<difference_type>::type

    using propagate_on_container_copy_assignment    = typename Get_propagate_on_container_copy_assignment<Alloc>::type;
    using propagate_on_container_move_assignment    = typename Get_propagate_on_container_move_assignment<Alloc>::type;
    using propagate_on_container_swap               = typename Get_propagate_on_container_swap<Alloc>::type;
    using is_always_equal                           = typename Get_is_always_equal<Alloc>::type;

    template <typename U>
    using rebind_alloc = typename Get_rebind_alloc_type<Alloc, U>::type;// | Alloc<U, Args...>;

    template <typename U>
    using rebind_traits = CustomAllocator_traits<typename rebind_alloc<U>>;

    /*rebind_alloc<T> = Alloc::rebind<T>::other  //if present,
                     = Alloc<T, Args> "if this Alloc is Alloc<U, Args>" // otherwise

    rebind_traits<T>	std::allocator_traits<rebind_alloc<T>>*/

public:
    static NODISCARD_CONSTEXPR pointer allocate(Alloc& allocator, const size_type count)
    {
#ifdef CXX_20_DYNAMIC_ALLOC
        if (Is_constant_evaluated)
#else   // CXX_20_DYNAMIC_ALLOC
        if constexpr (Has_MemberFunc_allocate<Alloc, size_type, const_void_pointer>::value)
#endif  // CXX_20_DYNAMIC_ALLOC
        {
            return allocator.allocate(count);
        }
        (void)allocator;
        return static_cast<pointer>(Allocate<NewAlignment<value_type>>(GetSizeOfCountNumOfT<sizeof(value_type)>(count)));
    }

    static NODISCARD_CONSTEXPR pointer allocate(Alloc& allocator, const size_type count, const_void_pointer hint)
    {
#ifdef CXX_20_DYNAMIC_ALLOC
        if (Is_constant_evaluated)
#else   // CXX_20_DYNAMIC_ALLOC
        if constexpr (Has_MemberFunc_allocate_hint<Alloc, size_type, const_void_pointer>::value)
#endif  // CXX_20_DYNAMIC_ALLOC
        {
            return allocator.allocate(count, hint);
        }
        return allocate(allocator, count);
    }

    static INLINE_OR_CONSTEXPR void deallocate(Alloc& allocator, pointer ptr, const size_type count)
    {
#ifdef CXX_20_DYNAMIC_ALLOC
        if (Is_constant_evaluated)
#else   // CXX_20_DYNAMIC_ALLOC
        if constexpr (Has_MemberFunc_deallocate<Alloc, pointer, const size_type>::value)
#endif  // CXX_20_DYNAMIC_ALLOC
        {
            allocator.deallocate(ptr, count);
        }
        (void)allocator;
        Deallocate<NewAlignment<value_type>>(ptr, GetSizeOfCountNumOfT<sizeof(value_type)>(count));
    }
    
    template <typename T, typename... Args >
    static INLINE_OR_CONSTEXPR void construct(Alloc& allocator, T* ptr, Args&&... args)
    {
        if constexpr (Uses_default_construct<Alloc, T*, Args...>::value)
        {
            (void)allocator;
#ifdef CXX_20_DYNAMIC_ALLOC
            Construct_at(ptr, std::forward<Args>(args)...);
#else   // CXX_20_DYNAMIC_ALLOC
            ::new (static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
#endif  // CXX_20_DYNAMIC_ALLOC
        }
        else
        {
            allocator.construct(ptr, std::forward<Args>(args)...);
        }
    }

    template <typename T>
    static INLINE_OR_CONSTEXPR void destroy(Alloc& allocator, T* ptr)
    {
        if constexpr (Uses_default_destroy<Alloc, T*>::value)
        {
#ifdef CXX_20_DYNAMIC_ALLOC
            Destroy_at(ptr);
#else   // CXX_20_DYNAMIC_ALLOC
            ptr->~T();
#endif  // CXX_20_DYNAMIC_ALLOC
        }
        else
        {
            return allocator.destroy(ptr);
        }
    }

    static NODISCARD_CONSTEXPR size_type max_size(const Alloc& allocator) noexcept
    {
        if constexpr (Has_MemberFunc_max_size<Alloc>::value)
        {
            return allocator.max_size();
        }
        else
        {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
    }

    static NODISCARD_CONSTEXPR Alloc select_on_container_copy_construction(const Alloc& allocator)
    {
        if constexpr (Has_MemberFunc_select_on_container_copy_construction<Alloc>::value)
        {
            return allocator.select_on_container_copy_construction();
        }
        else
        {
            return allocator;
        }
    }
};

// Alloc_ptr_t
template <typename Alloc>
using Alloc_ptr_t = typename CustomAllocator_traits<Alloc>::pointer;

// Alloc_size_t
template <typename Alloc>
using Alloc_size_t = typename CustomAllocator_traits<Alloc>::size_type;

// Rebind_alloc_t
template <typename Alloc, typename T>
using Rebind_alloc_t = typename CustomAllocator_traits<Alloc>::template rebind_alloc<T>;

// Is_simple_alloc_v
template <class Alloc> // tests if Custom allocator has simple addressing
INLINE_VAR constexpr bool Is_simple_custom_alloc_v = std::is_same_v<typename CustomAllocator_traits<Alloc>::size_type, size_t> &&
                    std::is_same_v<typename CustomAllocator_traits<Alloc>::difference_type, ptrdiff_t> &&
                    std::is_same_v<typename CustomAllocator_traits<Alloc>::pointer, typename Alloc::value_type*> &&
                    std::is_same_v<typename CustomAllocator_traits<Alloc>::const_pointer, const typename Alloc::value_type*>;

template <typename Alloc> // tests if STL allocator has simple addressing
INLINE_VAR constexpr bool Is_simple_STL_alloc_v = std::is_same_v<typename std::allocator_traits<Alloc>::size_type, size_t> &&
                    std::is_same_v<typename std::allocator_traits<Alloc>::difference_type, ptrdiff_t> &&
                    std::is_same_v<typename std::allocator_traits<Alloc>::pointer, typename Alloc::value_type*> &&
                    std::is_same_v<typename std::allocator_traits<Alloc>::const_pointer, const typename Alloc::value_type*>;

template <typename Alloc>
INLINE_VAR constexpr bool Is_simple_alloc_v = (Is_simple_custom_alloc_v<Alloc> || Is_simple_STL_alloc_v<Alloc>);


// Has_member_value_type
template <typename, typename = void >
struct Has_member_value_type : std::false_type { };

template <typename T>
struct Has_member_value_type<T, std::void_t<typename T::value_type>> : std::true_type { };


// Has_member_element_type
template <typename, typename = void >
struct Has_member_element_type : std::false_type { };

template <typename T>
struct Has_member_element_type<T, std::void_t<typename T::element_type>> : std::true_type { };

//Computes the value type of T.
//If std::iterator_traits<std::remove_cvref_t<T>> is not specialized,
//then std::iter_value_t<T> is std::indirectly_readable_traits<std::remove_cvref_t<T>>::value_type.
//Otherwise, it is std::iterator_traits<std::remove_cvref_t<T>>::value_type

#if USE_1
template<typename T, typename Enable = void>
struct Cond_value_type {};

template<typename T>
struct Cond_value_type<T, std::enable_if_t<std::is_object<T>::value>>
{
    using value_type = std::remove_cv_t<T>;
};

// Indirectly_readable_traits
template<typename T, typename Enable = void>
struct Indirectly_readable_traits;

template <typename T>
struct Indirectly_readable_traits<T*> : Cond_value_type<T> { };

template <typename T>
struct Indirectly_readable_traits<T, std::enable_if_t<std::is_array_v<T>>>
{
    using value_type = std::remove_cv_t<std::remove_extent_t<T>>;
};

template <typename T>
struct Indirectly_readable_traits<const T> : Indirectly_readable_traits<T> { };

template <typename T>
struct Indirectly_readable_traits<T, std::enable_if_t<Has_member_value_type<T>::value>> : Cond_value_type<typename T::value_type> { };

template <typename T>
struct Indirectly_readable_traits<T, std::enable_if_t<Has_member_element_type<T>::value>> : Cond_value_type<typename T::element_type> { };

template <typename T>
struct Indirectly_readable_traits<T, std::enable_if_t<Has_member_value_type<T>::value&& Has_member_element_type<T>::value>> : Cond_value_type<typename T::value_type> { };

template <typename T>
using __Iter_value_t = typename std::conditional_t<Is_from_primary<std::iterator_traits<Remove_cvref_t<T>>>::value,
        Indirectly_readable_traits<Remove_cvref_t<T>>,
        std::iterator_traits<Remove_cvref_t<T>>>::value_type;

template <typename T>
using Iter_value_t = __Iter_value_t<T>;
#endif // USE_1

#define USE_2
#ifdef USE_2
template <typename T>
using Iter_value_t = typename std::iterator_traits<T>::value_type;
#endif

// Construct_at
template<typename T, typename... Args, typename = std::void_t<decltype(::new(std::declval<void*>()) T(std::declval<Args>()...))>>
NODISCARD_CONSTEXPR T* Construct_at(T* const ptr, Args&&... args) noexcept(noexcept(::new (void_cast_ptr(ptr)) T(std::forward<Args>(args)...))) /* strengthened */
{
    return ::new (void_cast_ptr(ptr)) T(std::forward<Args>(args)...);
}

// Construct_in_place
template<typename T, typename... Args>
INLINE_OR_CONSTEXPR void Construct_in_place(T& value, Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
{
#ifdef CXX_20_DYNAMIC_ALLOC
    if (Is_constant_evaluated())
    {
        Construct_at(std::addressof(value), std::forward<Args>(args)...);
    }
    else
#endif  // CXX_20_DYNAMIC_ALLOC
    {
        ::new (void_cast_ptr(std::addressof(value))) T(std::forward<Args>(args)...);
    }
}

// Default_construct_in_place
template<typename T>
void Default_construct_in_place(T& value) noexcept(std::is_nothrow_default_constructible_v<T>)
{
    ::new (void_cast_ptr(std::addressof(value))) T;
}

// Destroy_range
template<typename Alloc>
INLINE_OR_CONSTEXPR void Destroy_range(Alloc_ptr_t<Alloc> first, const Alloc_ptr_t<Alloc> last, Alloc& allocator) noexcept
{
    // note that this is an optimization for debug mode codegen; in release mode the BE removes all of this
    using T = typename Alloc::value_type;
    if constexpr (!std::conjunction_v<std::is_trivially_destructible<T>, Uses_default_destroy<Alloc, T*>>)
    {
        for (; first != last; ++first)
        {
            CustomAllocator_traits<Alloc>::destroy(allocator, Unfancy(first));
        }
    }
}

// Destroy_range
template<typename NoThrowFwdIt, typename NoThrowSentinel>
INLINE_OR_CONSTEXPR void Destroy_range(NoThrowFwdIt first, const NoThrowSentinel last) noexcept
{
    // note that this is an optimization for debug mode codegen; in release mode the BE removes all of this
    if constexpr (!std::is_trivially_destructible_v<Iter_value_t<NoThrowFwdIt>>)
    {
        for (; first != last; ++first)
        {
            Destroy_in_place(*first);
        }
    }
}

// Destroy_in_place
template<typename T>
INLINE_OR_CONSTEXPR void Destroy_in_place(T& value) noexcept
{
    if constexpr (std::is_array_v<T>)
    {
        Destroy_range(value, value + std::extent_v<T>);
    }
    else
    {
        value.~T();
    }
}

// Destroy_at
template<typename T>
INLINE_OR_CONSTEXPR void Destroy_at(T* const ptr) noexcept /* strengthened */
{
#ifdef ENABLE_CXX_20
    if constexpr (std::is_array_v<T>)
    {
        Destroy_range(std::begin(*ptr), std::end(*ptr));
    }
    else
#endif  // ENABLE_CXX_20
    {
        ptr->~T();
    }
}
}
#endif	//#ifndef __CUSTOM_ALLOCATOR_TRAITS_H__