#include <bits/stdc++.h>
using namespace std;

class Card{
    private:
        string shape;
    public:
        Card(string s){shape=s;}
        //VIRTUAL FUNCTIONS TO BE OVERRIDEN
        virtual long long getArea()=0;
        virtual long long getedge1()=0;
        virtual long long getedge2()=0;
        string getShape(){
            return shape;
        }
        //COMPARATOR TO BE USED IN LIS
        bool operator<(Card* c){
            if(this->getArea()<c->getArea()){
                return true;
            }
            return false;
        }
    friend ostream& operator<<(ostream& stream,Card*& c);
    friend istream& operator>>(istream& stream,Card*& c);
};

//CLASS SQUARE
class Square : public Card{
    private:
        long long edge;
        long long area;
    public:
        //default constructor
        Square() :Card("SQUARE"),edge(0),area(0){}
        Square(long long e):Card("SQUARE"),edge(e),area(e*e){}
        long long getArea() override{
            return area;
        }
        long long getedge1()override{
            return edge;
        }
        long long getedge2()override{
            return edge;
        }
};

//CLASS RECTANGLE
class Rectangle : public Card{
    private:
        long long base;
        long long height;
        long long area;
    public:
        Rectangle():Card("RECTANGLE"),base(0),height(0),area(0){}
        Rectangle(long long b,long long h):Card("RECTANGLE"),base(b),height(h),area(b*h){}
        long long getArea()override{
            return area;
        }
        long long getedge1()override{
            return base;
        }
        long long getedge2()override{
            return height;
        }
};

//CLASS TRIANGLE
class Triangle : public Card{
    private:
        long long base;
        long long height;
        float area;
    public:
        Triangle():Card("TRIANGLE"),base(0),height(0),area(0){}
        Triangle(long long b,long long h):Card("TRIANGLE"),base(b),height(h),area(0.5f*b*h){}
        long long getArea()override{
            return static_cast<long long>(area);
        }
        long long getedge1()override{
            return base;
        }
        long long getedge2()override{
            return height;
        }
};

//OVERALOADING >> AND <<
istream& operator>>(istream& stream,Card*& c){
    string s;
    stream>>s;
    if(s=="SQUARE"){
        long long e;
        stream>>e;
        c=new Square(e);
        return stream;
    }
    else if(s=="RECTANGLE"){
        long long b;long long h;
        stream>>b>>h;
        c=new Rectangle(b,h);
        return stream;
    }
    else{
        long long b;long long h;
        stream>>b>>h;
        c=new Triangle(b,h);
        return stream;
    }
}

ostream& operator<<(ostream& stream,Card*& c){
    //we will print the graph here
    if(c->getShape()=="SQUARE"){
        stream<<"SQUARE "<<c->getedge1()<<"\n";
    }
    else if(c->getShape()=="RECTANGLE"){
        stream<<"RECTANGLE "<<c->getedge1()<<" "<<c->getedge2()<<"\n";
    }
    else{
        stream<<"TRIANGLE "<<c->getedge1()<<" "<<c->getedge2()<<"\n";
    }
    return stream;  
}

class CardOrganizer{
    private:
        //we will maintain stack of piles
        //and cards and pile index is its position in particular stack
        //pred is the immediate predeccesor in LIS
        vector<stack<Card*>> piles;
        vector<Card*> cards;
        vector<int> predecessors;
        vector<int> pile_index;
    public:
        //default constructor
        CardOrganizer(){
        }
        void addCard(Card* c){
            cards.push_back(c);
            //we will do a binary search with all stack top and find its place
            int low=0;int high=piles.size();
            while(low<high){
                int mid=(low+high)/2;
                if(c->getArea()>piles[mid].top()->getArea()){
                    //this can't be the stack so low is increase
                    low=mid+1;
                }
                else{
                    //obv less than this or this
                    high=mid;
                }
            }
            //after loop low will be the one that is allowed to put on stack
            if(low==piles.size()){
                //create a new stack and push it
                stack<Card*> s;
                s.push(c);
                piles.push_back(s);
            }
            else{
                //we can push it in low
                piles[low].push(c);
            }
            //now we need to push its index(to store in which pile our num is there)
            pile_index.push_back(low);
            //now we want to store the predecessor
            if(low==0){
                //no prev val so -1
                predecessors.push_back(-1);
            }
            else{
                //we have to find the lowerst one that has prev index
                for(int i=cards.size()-2;i>=0;i--){
                    if(pile_index[i]==low-1){
                        predecessors.push_back(i);
                        break;
                    }
                }
            }
        }
        size_t getPileCount() const{
            return piles.size();
        }
        vector<Card*> getLIS() const{
            //we will check the list
            vector<Card*> ans;
            int index=-1;
            int max_pile=-1;
            //we will iterate through and fix which one has highest pile index
            for(int i=pile_index.size()-1;i>=0;i--){
                if(pile_index[i]>max_pile){
                    max_pile=pile_index[i];
                    index=i;
                }
            }
            //now we will push them and go to next one using val we stored in predecessor
            while(index!=-1){
                ans.push_back(cards[index]);
                index=predecessors[index];
            }
            //we will loop through
            return ans;
        }
        
    friend class Square;
    friend class Triangle;
    friend class Rectangle;
};

int main(){
    long long q;cin>>q;
    CardOrganizer organiser;
    while(q--){
        int query;
        cin>>query;
        if(query==1){
            Card* c;
            cin>>c;
            organiser.addCard(c);
        }
        else if(query==2){
            cout<<organiser.getPileCount()<<"\n";
        }
        else{
            //query is 3
            vector<Card*> ans=organiser.getLIS();
            cout<<ans.size()<<"\n";
            for(int i=ans.size()-1;i>=0;i--){
                cout<<ans[i];
            }
        }
    }

}
