/**
* This small program exercises the wagon.
* It must do at least the parts that it contained when you copied it.
* You add some extra tests *after* those.
* I put my tests in a separate function. You should do the same.
* @author Beth Katz
*/

public class PileUp
{
   public static void redWagon( )
   {
      System.out.println("The red wagon holds 50 and already has 8 in it.");
      Wagon red = new Wagon(50, 8);

      System.out.println("Red wagon's available capacity is " 
                          + red.available( ) 
                          + " <-- of course 42 is right");
      red.load(20);
      System.out.println("Red wagon's available capacity is " 
                          + red.available( ));
      red.load(25);
      System.out.println("Red wagon's available capacity is " 
                          + red.available( ) + " <-- -3 is right");
      red.unload(10);
      System.out.println("Red wagon's available capacity is " 
                          + red.available( ));
      red.unload(90);
      System.out.println("Red wagon's available capacity is " 
                          + red.available( ) + " <-- 97 is right");
      System.out.println("The red wagon is ready for market.");
   }

   public static void greenWagon( )
   {
      System.out.println("The green wagon holds 25 and is empty.");
      Wagon green = new Wagon(25, 0);

      System.out.println("Green wagon's available capacity is " 
                          + green.available( ));
      green.unload(50);
      System.out.println("Green wagon's available capacity is " 
                          + green.available( ) + " <-- 75 is right");
      green.load(100);
      System.out.println("Green wagon's available capacity is " 
                          + green.available( ) + " <-- -25 is right");
      System.out.println("The green wagon is ready for market.");
   }

   public static void main(String[ ] args)
   {
      System.out.println("To market, to market ...");
      redWagon( );
      greenWagon( );
      System.out.println("Now we're ready for market.");
   }
}

