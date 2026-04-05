/*****************************************************************
* A wagon is a container a farmer hauls to market full of produce.
* It has a potential capacity and current contents. The user can
* load or unload it. This wagon should make *no* checks to ensure
* that the contents size remains "in bounds".
*
* Shawn Englerth
* CSCI 330
* October 28, 2003
*****************************************************************/

public class Wagon
{
    private int theCapacity; 
    private int theContents; 
    
    /*
      construct a wagon with capacity and contents
      @param capacity how much this wagon can hold
      @param contents how much the wagon currently holds
    */
    
    
    public Wagon(int capacity, int contents)
    {
	theCapacity = capacity;
	theContents = contents;
    }
    
    
    
    /**
       adds amount to the wagon
       @param amount how much to add to the wagon
       @return whether loading was successful
    */
    public boolean load(int amount)
    {
	theContents += amount;
	return (true);
    }
    
    
    
    /**
       removes amount to the wagon
       @param amount how much to remove from the wagon
       @return whether unloading was successful
    */
    public boolean unload(int amount)
    {
	theContents -= amount;
	return (true);
    }
    
    
    
    /**
       reports how much space remains in the wagon
       @return how much space is left in the wagon
    */
    public int available( )
    {
	return (theCapacity - theContents);
    }



    /**
       reports the load limit of the wagon
       @return the load limit of the wagon
    */
    public int getTheCapacity ()
    {
	return (theCapacity);
    }

    

    /**
       reports the current amount of load on the wagon
       @return the current amount of load on the wagon
    */
    public int getTheContents ()
    {
	return (theContents);
    }



    /**
       adds load to the current load of the wagon
       @param amount is the amount of load to add to current load
    */
    public void setTheContents (int amount)
    {
	if (amount <= theCapacity && amount >= 0)
	    theContents = amount;
	else 
	    theContents = theContents;
    }
}


