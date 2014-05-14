// wood.cpp  written by Duncan Murray, 1996. 
//
//  This program is the basis of a woodworkers calculator. It currently
//  works out the estimated costs of lengths of timber, based on size
//  and the type of timber.

#include    <iostream.h>
#include    <fstream.h>
#include	<stdio.h>
#include 	<string.h> 
#include    "wood.h"

Wood WoodDetails;                   //constructor
Type WoodType;                      //constructor
BeamSize WoodSize;                  // constructor
    

// member functions for the wood class
float Wood::CalcCost(int w, int h, float l) {
    float total;                    //total cost of the piece of wood
    float density_factor;           // denstity factor ( h * w )
    float span_factor;              // span factor ( h / w)
    float costpermm;                // cost for each type of wood
    
    density_factor = float(w) * float(h) / 1000;
    if(w > h)
        span_factor = (density_factor / 5) + ((float(w) / float(h)) / 10);
    else
        span_factor = (density_factor / 5) + ((float(h) / float(w)) / 10);
    costpermm = WoodType.costfactor(WoodType.GetName()); 
    total = density_factor * span_factor * l * costpermm * 2.1;      
    return total;
}

float Type::costfactor(char woodname[20])  {     // return costfactor
    // this function temporarily returns a fixed number calculated
    // as the costfactor for each type of wood. This will later be
    //in an INI file, to compensate for changing costs.
    float cost = 0;
    if(strncmp(woodname,     "Pine      ",4) == 0)   cost = 0.351; 
    else if(strncmp(woodname,"Permapine ",4) == 0)   cost = 0.580; 
    else if(strncmp(woodname,"Merranti  ",4) == 0)   cost = 0.400; 
    else if(strncmp(woodname,"Oregon    ",4) == 0)   cost = 0.650; 
    return cost;
}    

char *Type::GetName(void) {    //function to return name 
    return WoodType.woodname;
}   

void Type::AskName(void)   {
    char name[20];
    int answer = 1;
	cout << "\n\tSelect the type of timber :\n";
	cout << "\t1. Pine\n";
	cout << "\t2. Permapine\n";
	cout << "\t3. Merranti\n";
	cout << "\t4. Oregon\n";
	cout << "\t0. Exit\n";
    cin >> answer;
	switch (answer)   {
	    case 1:    { strcpy(name, "Pine      "); break;}
	    case 2:    { strcpy(name, "Permapine "); break;}
	    case 3:    { strcpy(name, "Merranti  "); break;}
	    case 4:    { strcpy(name, "Oregon    "); break;}
	    default:   { strcpy(name, "x");          break;}
    }
    strcpy(WoodType.woodname, name);     // put into class variable
}

int BeamSize::GetWidth(void)  {          //ask user for Width of Beam
    return WoodSize.Width;
}

int BeamSize::GetHeight(void) {          //ask user for Height of Beam
    return WoodSize.Height;
}

float BeamSize::GetLength(void) {        //ask user for Length of Beam
    return WoodSize.Length; 
}

void BeamSize::AskWidth(void)  {         //ask user for Width of Beam
    int width;
    cout << "\nEnter the width of the wood in millimetres   :";
    cin >> width;
    WoodSize.Width = width;
}


void BeamSize::AskHeight(void) {        //ask user for Height of Beam
    int height;
    cout << "\nEnter the Height of the wood in millimetres  :";
    cin >> height;
    WoodSize.Height = height;
}

void BeamSize::AskLength(void) {        //ask user for Length of Beam
    float length;
    cout << "\nEnter the Length of the wood in metres       :";
    cin >> length;
    WoodSize.Length = length;
}
   

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])

{
    int width = 0;              // width of wood
    int height = 0;             // height of wood
    float length;               // length of wood
    float totcost = 0;          // cost of wood
    float running_total = 0;    // running total of all timber lengths
    char woodname[20];
    char fname[80];             //filename to log wood costs to 
    if (argc > 1)
        strcpy(fname, argv[1]); //use filename entered on command line
    else
        strcpy(fname, "wood.log");    //use default filename
        
    ofstream logfile;           //declare output stream
    logfile.open(fname);        //open the file to hold 'shopping list'
    if (!logfile)   {
        cerr << "cant open " << fname << " for output.\n";
        return 1;               //quit the program
    }
  	logfile << "Timber           Height  Width   Length          Cost\n";
    
   	cout << "\n\t\t----------------------------\n";
	cout << "\n\t\t  Timber Costing Estimator\n\n"; 
	cout << "\t\t  written by Duncan Murray\n\n\n"; 
	cout << "\t\t----------------------------\n\n\n";
	cout << "\tThis program calculates the cost of a series of timber lengths\n\n";

    strcpy(woodname, "pine");   //inital value for while loop
    while(1)  {                 // loop until user finishes
        WoodType.AskName();                      // ask user for name
        strcpy(woodname, WoodType.GetName());    // get the name of the timber
        if (strlen(woodname) < 3) break;        // user chose to exit
        cout << "Enter the size of the " << woodname;
    	
	    // now get the details on the size
	    WoodSize.AskWidth();
	    WoodSize.AskHeight();
 	    WoodSize.AskLength();
 	    
	    width = WoodSize.GetWidth();
	    height = WoodSize.GetHeight();
 	    length = WoodSize.GetLength();
 	    
        // and calc. the cost of the timber
	    cout << "\nTotal Cost is  $" ;
        cout.width(10.2);
	    totcost = WoodDetails.CalcCost(width, height, length);
  	    cout << "Cost of Timber = " << totcost << "\n\n"; 
  	    running_total += totcost;
  	    
  	    // now append details to the cost file (if entered on command line)
  	    cout.width(20);
  	    logfile << woodname;
        cout.width(10);
  	    logfile << "\t" << width << "\t" <<  height << "\t" << length << "\t\t";
  	    logfile.width(10.2);
  	    logfile << totcost;
  	    logfile << "\n";
  	    
    }
    // output the running total of all timber lengths
    logfile << "\nTotal Cost = ";
    logfile.width(10.2);
    logfile << running_total;
    logfile.close();    //close the logfile
    return 0;
 }	


