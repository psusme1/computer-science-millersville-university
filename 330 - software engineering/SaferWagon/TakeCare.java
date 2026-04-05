/**
* This small program exercises the SaferWagon.
* @author Shawn Englerth
* November 11, 2003 (Veteran's Day! :-) )
*/

public class TakeCare
{
   public static void redWagon ()
   {
      System.out.println ("The red wagon holds 50 and already has 8 in it.");
      SaferWagon red = new SaferWagon (50, 8);

      System.out.println ("Red wagon's max available capacity is " 
                          + red.available () 
                          + " <-- of course 42 is right");
      red.load (20);
      System.out.println ("Load 20 onto red saferwagon.  Red saferwagon's available capacity is " 
                          + red.available () + " <-- 22 is correct.");
      red.load (25);

      System.out.println ("Load 25 onto red saferwagon.  Red saferwagon's available capacity is " 
			  + red.available () + " <-- 22 is correct. Load not performed / exceeded capacity");

      red.unload (10);
      System.out.println ("Unload 10 from red saferwagon.  Red saferwagon's available capacity is " 
                          + red.available () + " <-- 32 is correct.");

      red.unload (90);
      System.out.println ("Unload 90 from red saferwagon.  Red saferwagon's available capacity is " 
                          + red.available () + " <-- 32 is correct. Unload amount exceeded available amount");

      System.out.println ("The Capacity of the red saferwagon is " + red.getTheCapacity () + ".  <-- 50 is correct");
      System.out.println ("The Load of the red saferwagon is " + red.getTheContents () + ".  <-- 18 is correct");

      System.out.println ("Set the load of the red saferwagon to 50.");
      red.setTheContents (50);
      System.out.println ("The Load of the red saferwagon is " + red.getTheContents () + ".  <-- 50 is correct.");
      
      System.out.println ("Set the load of the red saferwagon to 51.");
      red.setTheContents (51);
      System.out.println ("The Load of the red saferwagon is " + red.getTheContents () + ".  <-- 50 is correct.");
      
      
      
      System.out.println ("The red wagon is ready for market.");
   }
    
    public static void greenWagon ()
    {
       System.out.println ("The green wagon holds 25 and is empty.");
       SaferWagon green = new SaferWagon (25, 0);


      System.out.println ("Green wagon's max available capacity is " 
                          + green.available () 
                          + " <-- of course 25 is right");
      green.load (20);
      System.out.println ("Load 20 onto green saferwagon.  Green saferwagon's available capacity is " 
                          + green.available () + " <-- 5 is correct.");
      
      green.load (25);
      System.out.println ("Load 25 onto green saferwagon.  Green saferwagon's available capacity is " 
			  + green.available () + " <-- 5 is correct. Load not performed / exceeded capacity");

      green.unload (10);
      System.out.println ("Unload 10 from green saferwagon.  Green saferwagon's available capacity is " 
                          + green.available () + " <-- 15 is correct.");

      green.unload (90);
      System.out.println ("Unload 90 from green saferwagon.  Green saferwagon's available capacity is " 
                          + green.available () + " <-- 15 is correct. Unload amount exceeded available amount");

      System.out.println ("The Capacity of the green saferwagon is " + green.getTheCapacity () + ".  <-- 25 is correct");
      System.out.println ("The Load of the green saferwagon is " + green.getTheContents () + ".  <-- 10 is correct");
      
      System.out.println ("Set the load of the green saferwagon to 25.");
      green.setTheContents (25);
      System.out.println ("The Load of the green saferwagon is " + green.getTheContents () + ".  <-- 25 is correct.");
      
      System.out.println ("Set the load of the green saferwagon to 51.");
      green.setTheContents (51);
      System.out.println ("The Load of the green saferwagon is " + green.getTheContents () + ".  <-- 25 is correct.");

      System.out.println ("Set the load of the green saferwagon to 0.");
      green.setTheContents (0);
      System.out.println ("The Load of the green saferwagon is " + green.getTheContents () + ".  <-- 0 is correct.");
      
      System.out.println ("Set the load of the green saferwagon to -1.");
      green.setTheContents (-1);
      System.out.println ("The Load of the green saferwagon is " + green.getTheContents () + ".  <-- 0 is correct.");

      
      System.out.println ("The green wagon is ready for market.");       
    
}

public static void main (String [] args)
{
    System.out.println ("To market, to market ...");
      redWagon ();
      greenWagon ();
      System.out.println ("Now we're ready for market.");
   }
}

