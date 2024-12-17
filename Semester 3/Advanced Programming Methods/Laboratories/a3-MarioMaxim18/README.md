# Laboratory 3

<!--
**Lab assignment**

For the class implemented for Lab assignment 2, design and implement an in-memory repository using Java generics. The repository should contain the CRUD operations. Please see the attached diagram as an example. Write a test program for the in-memory repository that will:
-	Add 5 elements to the repository;
-	Print all the elements, sorted by a given criterion (only one is sufficient);
-	Search for an element;
-	Delete an element;
-	Update an element;

---

**Home assignment**
-->

Continue designing and implementing the problem you have chosen. For the next lab you must:
-	Implement classes in the repository that allow storing and retrieving data in two formats: text files and binary files (using the Java serialization mechanism). The program must work identically using text and binary file repositories. The decision of which repositories are employed, as well as the location of the repository input files will be made available via the program’s **settings.properties** file and the Java *Properties* class. See an example of this file below:

> Repository = binary \
> Patients = “patients.bin” \
> Appointments = “appointments.bin”

-	Provide tests using JUnit. The test coverage for at least one entity (throughout all layers except UI) must be more than 95%.

**Bonus (0.2p)** \
Create and use custom Validator classes to validate your inputs. Provide validator objects to your service(s) and make sure validation is performed. For the bonus points create at least one Validator class for each entity.

