#ifndef CARDCLASS_H
#define CARDCLASS_H


class CardClass
{
    public:
        explicit CardClass(int);
        CardClass(int , int);
        virtual ~CardClass();
        bool operator == (CardClass rhs) {
       return (x == rhs.x && y == rhs.y)? true : false;
    }
    protected:
    private:
        int x;
        int y;
};

#endif // CARDCLASS_H
