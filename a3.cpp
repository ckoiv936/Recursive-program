//Still need to: print only fastest
//Valgrind

/*
Chad Koivuneva
ckoiv936@mtroyal.ca
comp1633
a3.cpp
Paul Pospisil
Due: March 4th 2020
Purpose: The program finds the shortest possible time to go from start to finish
in a grid whose size can vary. The route must go through every intersection 
in the grid

Details: 
Input: enter the size of the grid. Fills the grid with a false in every 
intersection
Output: Fastest time, fastest path and the number of possible paths

This program uses no while loops (besides initializing the grid), and solely 
relies on recursion.How recursion works is the function loops itself while
 changing parameters, making it easy todo things in reverse. The program
 heavily relies on it to backtrack when finding a correct path.
If you hit a dead end, you need to backtrack and try a different path

Limitations: If a grid size greater than 6 is entered, will take a very long
 time. Otherwise, 
the grid can also not be larger than 10

Currently all paths are printed, instead of only the fastest

*/

#include <iostream>
using namespace std;
//The maxsize of a grid someone can enter
const int MAXSIZE = 9;
//array of type grid used for the paths
typedef bool grid[MAXSIZE][MAXSIZE];
//Declaring a pointer to a Node with properties of a Node
typedef struct Node* NodePtr;
struct Node
{//Each node has a place for x,y coordinate and address to next node
    NodePtr next;
    int x;
    int y;
}; 
//Find path finds how to get from start to finish and then calls helper
//functions to print the results
void findpath(grid g,int x, int y, int endx, int endy,bool &done, int size,
 int &solution, NodePtr head,
 bool incomplete, int& mintime);
//Checks if the next move is available
bool canmove(grid g, int size, int x, int y);
//Checks if array has been filled
bool scanarray(grid g,int,int,int);
//Stores solution into a linked list
void storesolution(grid g,int size, int x, int y,NodePtr& head);
//writes a linked list out
void writesolution(NodePtr head);
//Removes an incorrect movement choice that had to be backtracked
void removepath(NodePtr head);
//Finds the time of each path
int findtime(NodePtr head);
//Removes a list of solutions 
void removesolution(NodePtr head);



int main()
{
//Initializing a large grid, giving user option for grid size
    int size;
//Where the start and end of the grid are, in coordinates x,yy
    int startx, starty, endx, endy;
//Used for initializing the grid and setting all values to false
    int count1 =0;
    int count2 = 0;
//If path is complete, done
    bool done = false;
//Name of the grid
    grid g;
//Counter for number of solutions
    int solution = 0;
//If end has been reached without array being filled
    bool incomplete = false;
//The quickest time for all solutions
    int mintime = 0;
    cout<<"Grid size: ";
    cin>>size;
    //set each spot to false
    while(count2<=size)
    {
	while(count1<size)
	{
	    g[count1][count2] = false;
	    count1++;
	}
//Count1,count2 are x,y and alternate so every coordinate pair is false
	g[count1][count2] = false;
	count2++;
	count1=0;
    } 
//Grid creation done ////////////////////////////////////////////////////////

//Node creation
    NodePtr head = new Node;
    head = NULL;
    
//Finding path of grid
    startx = 0;
    starty = 0;
    endx = 0;
    endy = size-1;
    
    findpath(g,startx,starty,endx,endy,done,size, solution,head,incomplete,
	     mintime);

    cout<< "number of solutions: " << solution;
    cout<<endl<<"Minimum time: "<<mintime;
    
    removesolution(head);

    return 0;
} 
///////////////////////////////////////////////////////////////////////////
// Function name: findpath
//
// Purpose: given a start and end, finds all possible paths to the finish.
// Also calls helper functions to determine the time for the paths and the
// quickest time as well as counting the number of solutions
// Details: Each run of the function, 1 new position in the grid is tried.
// If the finish is reached without meeting all intersections, or a move
// cannot be done, need to backtrack and try again.
// base case: end has been reached, all intersections visited
//
// recursive case: ending has not been reached, grid not filled.
// try and move somewhere until condition met
//
// Input: Start and end positions. Grid with size. 
//
// Output: Min time, number of solutions, path's of each solution
//
//

void findpath(grid g,int x, int y, int endx, int endy,bool &done, int size,
 int &solution,NodePtr head, bool incomplete,int& mintime)

{   //Count's equivalent to x,y of the grid
    int count1 = 0;
    int count2 = 0;
    //Initially 0, tracks how long each path took
    int time = 0;
    //When a path has been taken, mark as true 
    g[x][y] = true;
    
    storesolution(g,size,x,y,head);
    //If reached the end, but not every intersection
    if((x == 0) && (y == (size-1)) && !scanarray(g,size,count1,count2))
	incomplete = true;
    //Reached end and every intersection
    if (scanarray(g, size,count1,count2) && (endx == x) && (endy == y))
    {
	
	done = true;
	
    }	
    else //Try moving in any 4 directions 
    {
	/* 
	   right: (x+1)
	   up: (y+1)
	   left: (x-1)
	   down: (y-1) 
	*/ 
	if (!done && canmove(g,size,x+1,y) && (incomplete == false))
	{
	    findpath(g,x+1,y,endx,endy,done,size,solution,head,incomplete,
		     mintime);
	}
	if(!done && canmove(g,size,x,y+1) && (incomplete == false))
	{
	    findpath(g,x,y+1,endx,endy,done,size,solution,head,incomplete,
		     mintime);
	} 
	if(!done && canmove(g,size,x-1,y) && (incomplete == false))
	{
	    
	    findpath(g,x-1,y,endx,endy,done,size,solution,head,incomplete,
		     mintime);
	} 
	if(!done && canmove(g,size,x,y-1) && (incomplete == false))
	{
	    findpath(g,x,y-1,endx,endy,done,size,solution,head,incomplete,
		     mintime);
	} 
//After path has been found, increase solutions
	     
    }
    if (done)    
	
    {
	solution++;
	//done back to false so function tries more solutions
	done = false;
	//comparing time with other solutions
	time = findtime(head);
	//Writing the solution
	//writesolution(head);
	
	cout<<endl;
	if(mintime ==0)
	{
	   
	    // copypath(head,head2); 
	    mintime = time; //Copy the path as the fastest one
	}
	else
	{
	    if (time<mintime)
	    {
		mintime = time;  
	    } 
	} 
	

	

    } //If it was incomplete, set back to false since backtracking
    incomplete = false;
    
    g[x][y] = false;
    //Get rid of the path because it was backtracked
    removepath(head);

    return;
}  
///////////////////////////////////////////////////////////////////////////
// Function name: canmove
//
// Purpose: test if a movment in the grid can be made
//
//
// Details: Based on the size of the grid. A movement cannot be made if:
// Intersection has already been visited.
// Movement off the grid
//
// Input: A movement command
//
// Output: true or false if you can move that way
//
//
    
bool canmove(grid g, int size, int x,int y)

{

    bool result;
    
    result = false;
    if((x >= 0 && x<size)&&(y>= 0 && y<size) && (g[x][y] != true)) 
    {
	result = true;
    }


    return result;

} 
///////////////////////////////////////////////////////////////////////////
// Function name: scanarray 
//
// Purpose: Scans if entire grid has been filled
//
//
// Details: If there is ever a coordinate that is still false, the scan 
// returns false and solution is not complete
// 
// base case: Every path visited, return true
//
// recursive case: scan a new path and check if its been visited
//
// Input: grid and size
//
// Output: if its a complete solution
//
//

bool scanarray(grid g, int size,int count1,int count2) 
{
    bool good = true;
        
    
    if(count2>=size); //base case: max index
       
    else
    {//recurive: increase y coordinate by 1 if x has maxed out
	if(count1==size)
	{ 
	    count2++;
	    count1=0;
	}
	//If y coordinate maxes then every coordiante has been visited
	//and the soution is correct
	if(count2<size)
	    good = g[count1][count2];
	if(good == true)
	    good = scanarray(g,size,count1+1,count2);   
    }	 
    
    return good;
} 
///////////////////////////////////////////////////////////////////////////
// Function name: storesolution 
//
// Purpose: Given an intersection that has not been visited, store into
// its path
//
// Details: Using a linked list, store the coordinates of the intersection
// as data into the linked list. Make a new Node for the data and set it 
// to point to head, and head to NULL
// 
// base case: Head is Null, insert a node in front of head
//
// recursive case: head->next != NULL, navigate till it does so
// the new data is being inserted on the end of the list
//
// Input: A pointer to a linked list, grid and coordinates
//
// Output: The coordinates in order of when they occured 
//
//

void storesolution(grid g,int size, int x, int y,NodePtr& head)
{

    if (head == NULL)
    {
	NodePtr temp = new Node;
	head = temp; 
	temp -> x = x;
	temp -> y = y;
	head ->next = NULL;


    } 

    else 
	storesolution(g,size,x,y,head->next);
    
    

    return;
} 
///////////////////////////////////////////////////////////////////////////
// Function name: writesolution
//
// Purpose: prints out a solution
//
//
// Details: Given the head of a list, writes each data entry until
// head = NULL
// 
// base case: head = NULL
//
// recursive case: head != NULL, print out the coordinates and go to next
// node
// Input: a pointer to a head node 
//
// Output: a grid solution path
//
//

void writesolution(NodePtr head)
{
    if (head != NULL)
    {
	cout<<"("<<head->x<<","<<head->y<<")";
	writesolution(head->next);
    } 


    return;
} 
///////////////////////////////////////////////////////////////////////////
// Function name: removepath
//
// Purpose: If a solution was saved but later had to be backtracked, 
// the solution must be removed from the list
//
// Details: Remove an item from the end of a linked list. Done
// recursivly so it first scans until the end has been found, then
// removes it.
// base case: Only 1 node with data. delete the node and set a temp 
// pointer to NULL
//
// recursive case: traverse until the next one will be NULL. In the code
// written next->next because it goes next each recursion
// Input: A pointer to a list of locations visited
//
// Output: The last location visited removed
//
//

void removepath(NodePtr head)
{
    //Temp pointer that marks the location of head so other nodes arent 
    //lost
    NodePtr temp=NULL; 
    
    if(head->next == NULL)
    {
	delete head;
	if(temp==NULL)
	    head = NULL;
	else
	    temp->next = NULL;
    }
    else
    {//If NULL is not coming up this time, reset with temp = head
	//traverse until NULL is the next node
    if(head->next != NULL && head->next->next == NULL)
	temp = head;
    removepath(head->next);
	if(head == temp)
	    temp->next = NULL;
    
    }
       
    return;
}
///////////////////////////////////////////////////////////////////////////
// Function name: findtime
//
// Purpose: finds the time a path takes
//
//
// Details: Due to the nature of the chart, when x coordinate is not 
// changing, its speed deppends on its new x value,+1 since the grid starts
// at 0 but the speed at 10. Computes time using v = d/t
// 
// base case: Only 1 path to find the time
//
// recursive case: Find time and add it to time each time a coordinates 
// time is processed
// Input: A pointer to a list of moves in the grid
//
// Output: The time it took the solution
//
//

int findtime(NodePtr head)
{
    
    int oldx = 0;
    int newx=0;
    int oldy=0;
    int newy =0;
    int time = 0;
    
//at our destination, time is constant
    if(head->next == NULL || head == NULL)
	time = 0;
    else
    {
	oldx = head->x;
	newx = head->next->x;
	
	
	oldy = head->y;       
	newy = head->next->y;

	//if moved in y direciton, speed depends on x
	if(oldx  == newx)
	{
	    
	    time = 60/(newx+1);
	}
	else if(newy == oldy)
	{  
	    time = 60/(newy+1);
	    
	}
	//Add time to running total and find new time
	time = time + findtime(head->next);
	
    }

    return time;
} 
///////////////////////////////////////////////////////////////////////////
// Function name: removesolution
//
// Purpose: Returns an entire list back to the heap
// 
//
// Details: Given the location of a list, removes the entire solution
// by deleting head until it equals NULL
// 
// base case: nothing to delete
//
// recursive case: More nodes in list that arent NULL
//
// Input: A pointer to a solution
//
// Output: N/A
//
//

void removesolution(NodePtr head)
{

     if (head== NULL);
    else
    {
	
	removepath(head->next);
	delete head;
    } 
    
    //head = NULL to close off the list
   
    
    return;


} 
