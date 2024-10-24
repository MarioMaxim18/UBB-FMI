import domain.Doctor;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static boolean sequentialSearch(int n, int[] arr)
    {
        for(int i = 0; i < arr.length; i++)
            if(arr[i] == n)
                return true;
        return false;
    }

    public static boolean binarySearch(int n,int l,int r, int[] arr)
    { while(l <= r)
    { int mid = (l+r)/2;
        if(arr[mid] == n)
        {return true;}
            if(arr[mid] < n)
                l = mid + 1;
            if(arr[mid] > n)
                r = mid - 1;}
        return false;
    }
    public static boolean binarySearch2(int n,int [] arr)
    {
        return binarySearch(n,0,arr.length-1,arr);

    }

    public static void main(String[] args) {
//        String a = "2";
//        int x = Integer.parseInt(a);
//        System.out.println(x);

//        if (args.length != 2)
//            System.out.println("Please provide at least 2 arguments.");
//
//        int[] int_array = new int[args.length-1];
//        for(int i = 1; i < args.length; i++)
//            int_array[i-1]=Integer.parseInt(args[i]);
//
//        int n = Integer.parseInt(args[0]);
//        //boolean found =sequentialSearch(Integer.parseInt(args[0]), int_array);
//        boolean found =binarySearch2(Integer.parseInt(args[0]), int_array);
//        if(found)
//            System.out.println("Number " + n + " was found.");
//        else
//            System.out.println("Number " + n + " was not found.");

        Doctor d1 = new Doctor(1, "Popescu", "cardiology", 5);
        Doctor d2 = new Doctor(2, "Gerogescu", "ORL", 5);
        System.out.println(d1.equals(d2));
    }
}