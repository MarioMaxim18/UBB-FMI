import Repository.Repository;
import domain.Doctor;
import domain.Entity;
import domain.Patient;
import Repository.FilteredRepository;
import filter.FilterDoctorsBySpecialty;

import java.util.Iterator;

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
    public static void printElems(Repository r){
        Iterator<Entity> Iterator = r.iterator();
        while(Iterator.hasNext())
            System.out.println(Iterator.next());
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
//        System.out.println(d1.equals(d2));

        Doctor d3 = new Doctor(3, "Popescu2", "cardiology", 7);
        Doctor d4 = new Doctor(4, "Gerogescu2", "ORL", 9);

        Repository doctorsRepo= new Repository();
        Repository patientsRepo= new Repository();

        doctorsRepo.add(d1);
        doctorsRepo.add(d2);
        doctorsRepo.add(d3);
        doctorsRepo.add(d4);

        Patient p1=new Patient(12,"Mihai",1234);
        Patient p2=new Patient(13,"Mihai2",1274);
        patientsRepo.add(p1);
        patientsRepo.add(p2);

       /* printElems(doctorsRepo);
        printElems(patientsRepo);*/

        FilteredRepository filteredRepo = new FilteredRepository(new FilterDoctorsBySpecialty("cardiology"));
        filteredRepo.add(d1);
        filteredRepo.add(d2);
        filteredRepo.add(d3);
        filteredRepo.add(d4);
        printElems(filteredRepo);
    }
}