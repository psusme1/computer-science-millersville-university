/*****************************************************************
 * A safer wagon is a container a farmer hauls to market full of produce.
 * It has a potential capacity and current contents. The user can
 * load or unload it. This wagon should makes checks to ensure
 * that the contents size remains "in bounds".
 *
 * Shawn Englerth
 * CSCI 330
 * October 28, 2003
 *****************************************************************/

public class SaferWagon extends Wagon
{
    /*
      construct a wagon with capacity and contents
      @param capacity how much this wagon can hold
      @param contents how much the wagon currently holds
    */
    
    
    public SaferWagon(int capacity, int contents)
    {
	super (capacity, contents);
    }
    
    
    
    /**
       adds amount to the wagon
       @param amount how much to add to the wagon
       @return whether loading was successful
    */
    public boolean load (int amount)
    {
        if (super.getTheContents () + amount <= super.getTheCapacity ())
	    {
		super.load (amount);
		return (true);
	    }
	else
	    return (false);
    }
    
    
    
    /**
       removes amount to the wagon
       @param amount how much to remove from the wagon
       @return whether unloading was successful
    */
    public boolean unload (int amount)
    {
	if (super.getTheContents () - amount >= 0)
	    {
		setTheContents ((super.getTheContents () - amount));
		return (true);
	    }
	else 
	    return (false);
    }
}
