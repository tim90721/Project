#include "random_access.h"

using namespace std;

int binarySearchPreamble(const vector<RAR*>& subframeRars, const int raoLeft, const int raoRight, const int raoFoundIndex, const int preambleIndex){
    if(raoLeft == -1 && raoRight == -1)
        return raoFoundIndex;
    int left = raoLeft;
    int right = raoRight;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(subframeRars[mid]->preambleIndex > preambleIndex)
            right = mid - 1;
        else if(subframeRars[mid]->preambleIndex < preambleIndex)
            left = mid + 1;
        else
            return mid;
    }
    if((unsigned)left == subframeRars.size())
        return left;
    else{
        if(left < raoRight){
            return (preambleIndex > subframeRars[left]->preambleIndex)?(left + 1):left;
        }
        else 
            return (preambleIndex > subframeRars[raoRight]->preambleIndex)?(raoRight + 1):raoRight;
    }
}

int binarySearchRAO(const vector<RAR*>& subframeRars, int* raoLeft, int* raoRight, const int raoIndex){
    *raoLeft = -1;
    *raoRight = -1;
    if(subframeRars.size() == 0){
        return 0;
    }
    else{
        int left = 0;
        int right = subframeRars.size() - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            //printf("left: %d, right: %d\n", left, right);
            //printf("mid: %d\n", mid);
            //printf("rar mid rao: %d, rao: %d\n", 
            //        subframeRars[mid]->raoIndex,
            //        raoIndex);
            if(subframeRars[mid]->raoIndex < raoIndex)
                left = mid + 1;
            else if(subframeRars[mid]->raoIndex > raoIndex)
                right = mid - 1;
            else if(subframeRars[mid]->raoIndex == raoIndex){
                *raoLeft = mid;
                *raoRight = mid;
                //printf("rao left: %d, rao right: %d\n", *raoLeft, *raoRight);
                while((*raoLeft) > 0 && subframeRars[(*raoLeft) - 1]->raoIndex == raoIndex)
                    (*raoLeft)--;
                while((unsigned)(*raoRight) + 1 < subframeRars.size() && subframeRars[(*raoRight) + 1]->raoIndex == raoIndex)
                    (*raoRight)++;
                return mid;
            }
        }
        //printf("left: %d, right: %d\n", left, right);
        //printf("rao left: %d, rao right: %d\n", *raoLeft, *raoRight);
        if((unsigned)left == subframeRars.size())
            return left;
        else if(raoIndex > subframeRars[left]->raoIndex)
            return left + 1;
        else
            return left;
    }
}

int binarySeachMsg3(const vector<Msg3*>& msg3s, const int tc_rnti){
    if(msg3s.size() == 0)
        return 0;
    int left = 0;
    int right = msg3s.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(msg3s[mid]->tc_rnti < tc_rnti)
            left = mid + 1;
        else if(msg3s[mid]->tc_rnti > tc_rnti)
            right = mid - 1;
        else
            return mid;
    }
    if((unsigned)left == msg3s.size())
        return left;
    else if(tc_rnti > msg3s[left]->tc_rnti)
        return left + 1;
    else
        return left;
}

int searchRAR(const vector<RAR*>& subframeRars, const int raoIndex, const int preambleIndex){
    int raoLeft, raoRight;
    int raoInsertIndex = binarySearchRAO(subframeRars, &raoLeft, &raoRight, raoIndex);
    
    //printf("raoLeft: %d, raoRight: %d\n", 
    //        raoLeft,
    //        raoRight);
    //printf("rao insert index: %d\n", raoInsertIndex);
    if((unsigned)raoInsertIndex == subframeRars.size())
        return raoInsertIndex;
    int preambleInsertIndex = binarySearchPreamble(subframeRars, raoLeft, raoRight, raoInsertIndex, preambleIndex);
    return preambleInsertIndex;
}

int searchRAR(const vector<RAR*>& subframeRars, RAR &rar){
    return searchRAR(subframeRars, rar.raoIndex, rar.preambleIndex);
}

int searchMsg3(const vector<Msg3*>& msg3s, const int tc_rnti){
    return binarySeachMsg3(msg3s, tc_rnti);
}

int searchMsg3(const vector<Msg3*>& msg3s, Msg3& msg3){
    return searchMsg3(msg3s, msg3.tc_rnti);
}
