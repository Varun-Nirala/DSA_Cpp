#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

/**
 * Save humans, destroy zombies!
 **/
typedef struct HStruct
{
    int id;
    int x, y;
}HStruct;

typedef struct ZStruct
{
    int id;
    int x, y;
    int nextX, nextY;
}ZStruct;

vector<HStruct> hVector;
vector<ZStruct> zVector;

int findDistance(int x1, int y1, int x2, int y2)
{
    int yDis, xDis;
    int ans = 0;
    yDis = abs(y2-y1);
    xDis = abs(x2-x1);
    ans = xDis*xDis + yDis*yDis;
    ans = (int)sqrt(ans);
    return ans;
}

int moveTowardZombie()
{
    int size = (int)zVector.size();
    vector<int> zombieCircle(size, 0);
    
    int max = -1;
    int id = size;
    for(int i = 0; i < size; ++i)
    {
        int x = zVector[i].x;
        int y = zVector[i].y;
        
        int minX, maxX, minY, maxY;
        
        minX = x-2000 < 0 ? 0 : x-2000;
        maxX = x+2000 > 16000 ? 16000 : x+2000;

        minY = y-2000 < 0 ? 0 : y-2000;
        maxY = y+2000 > 9000 ? 9000 : y+2000;
        
        
        for(int j = 0; j < size; ++j)
        {
            if(i == j)
                continue;
            
            if((zVector[j].nextX >= minX || zVector[j].nextX <= maxX)
                && (zVector[j].nextY >= minY || zVector[j].nextY <= maxY))
            {
                zombieCircle[i]++;
            }
        }
        if(max < zombieCircle[i])
        {
            max = zombieCircle[i];
            id = i;
        }
    }
    
    return id;
}

int NumberOfHumanWeCanSave(int ashX, int ashY, vector<int> &vHumanId, vector<int> &vStepDiff)
{
    int weCanSave = 0;
    //int zombieToHuman = INT_MAX;
    
    int sizeZ = (int)zVector.size();
    int sizeH = (int)hVector.size();
    
    vector<int> stepsFromZombie(sizeH, INT_MAX);
    vector<int> stepsFromAsh(sizeH, INT_MAX);
    int x, y;
    
    int numberOfSteps;
    
    for(int i = 0; i < sizeH; i++)
    {
        x = hVector[i].x;
        y = hVector[i].y;
        
        stepsFromAsh[i] = findDistance(x, y, ashX, ashY)/1400;
        
        for(int j = 0; j < sizeZ; j++)
        {
            numberOfSteps = findDistance(x, y, zVector[j].x, zVector[j].y)/400;
            if(stepsFromZombie[i] > numberOfSteps)
            {
                stepsFromZombie[i] = numberOfSteps;
            }
        }
    }
    
    vHumanId.clear();
    vStepDiff.clear();
    for(int i = 0; i < sizeH; i++)
    {
        if(stepsFromAsh[i] <= stepsFromZombie[i])
        {
            weCanSave++;
            vHumanId.push_back(i);
            vStepDiff.push_back(stepsFromZombie[i] - stepsFromAsh[i]);
        }
        cerr << "SFromAsh = " << stepsFromAsh[i] << ", SFromZ = " << stepsFromZombie[i] << endl;
    }
    
    cerr << "WeCanSave = " << weCanSave << endl;
    return weCanSave;
}
 
void test_codeVsZombies()
{
    // game loop
    while (1)
	{
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        int humanCount;
        hVector.clear();
        zVector.clear();
        cin >> humanCount; cin.ignore();
        for (int i = 0; i < humanCount; i++)
		{
            int humanId;
            int humanX;
            int humanY;
            cin >> humanId >> humanX >> humanY; cin.ignore();
            HStruct humanS;
            humanS.id = humanId;
            humanS.x = humanX;
            humanS.y = humanY;
            hVector.push_back(humanS);
        }
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        for (int i = 0; i < zombieCount; i++)
		{
            int zombieId;
            int zombieX;
            int zombieY;
            int zombieXNext;
            int zombieYNext;
            cin >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; cin.ignore();
            
            ZStruct zombieS;
            zombieS.id = zombieId;
            zombieS.x = zombieX;
            zombieS.y = zombieY;
            zombieS.nextX = zombieXNext;
            zombieS.nextY = zombieYNext;
            zVector.push_back(zombieS);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int moveX, moveY;
        int humanWeCanSave;
        
        vector<int> vHumanId;
        vector<int> vStepDiff;
        humanWeCanSave = NumberOfHumanWeCanSave(x, y, vHumanId, vStepDiff);
        
        for(int i = 0; i < vStepDiff.size(); i++)
        {
            for(int j = i+1; j < vStepDiff.size(); j++)
            {
                int temp;
                if(vStepDiff[i] > vStepDiff[j])
                {
                    temp = vStepDiff[i];
                    vStepDiff[i] = vStepDiff[j];
                    vStepDiff[j] = temp;
                
                    temp = vHumanId[i];
                    vHumanId[i] = vHumanId[j];
                    vHumanId[j] = temp; 
                }
            }
        }
        
        
        if(humanWeCanSave <= 2 && vStepDiff.size() && vStepDiff[0] < 2)
        {   
            if(vHumanId.size())
            {
                moveX = hVector[vHumanId[0]].x;
                moveY = hVector[vHumanId[0]].y;
            }
            else
            {
                moveX = hVector[0].x;
                moveY = hVector[0].y;
            }
        }
        else if(humanWeCanSave <= 1)
        {
            if(vHumanId.size())
            {
                moveX = hVector[vHumanId[0]].x;
                moveY = hVector[vHumanId[0]].y;
            }
            else
            {
                moveX = hVector[0].x;
                moveY = hVector[0].y;
            }
        }
        else
        {   
            /*for(int i = 0; i < vStepDiff.size(); i++)
            {
                cerr<< "vStedDiff[" << i << "] = " << vStepDiff[i] << "vHumanId[" << i << "] = " << vHumanId[i] << endl;
            }*/

            int tempid = moveTowardZombie();
            cerr << "Move toward zombie" << endl;
            moveX = zVector[tempid].nextX;
            moveY = zVector[tempid].nextY;
        }
        cout << moveX << " " << moveY << endl; // Your destination coordinates
    }
}