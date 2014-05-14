//  Wood.h       written by Duncan Murray
//  defines class memebers for the WOOD calcualtion project

class Wood {
protected:
    float cost;
    double span;
public:
    //Wood(double Initcost, double Initspan);
    float CalcCost(int w, int h, float l);      // function to calculate cost of wood
    //double CalcSpan(void);    // function to calculate max. span of length
};
class Type : public Wood    {   //derived from wood class
protected:
    char filename[80];          // filename of costs for each size
    char woodname[20];          // name of the wood
public:
    char *GetName(void);        // returns name of wood
    void AskName(void);        // asks user for name
    float costfactor(char[20]);     // return / calculate costfactor
};

class BeamSize : public Wood {  //derived from class wood
protected:
    int Width;                  //width of the beam
    int Height;                 //height of the beam
    float Length;               //length of the beam
public:
    int GetWidth(void);         //get Width of Beam
    int GetHeight(void);        //get Height of Beam
    float GetLength(void);      //get Length of Beam
    void AskWidth(void);        //ask user for Width of Beam
    void AskHeight(void);       //ask user for Height of Beam
    void AskLength(void);       //ask user for Length of Beam
};
