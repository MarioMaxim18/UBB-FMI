# Laboratory 4

Continue the implementation of the problem you have chosen for home assignment 2. For the next lab you must:
-	Implement classes in the repository that allow storing and retrieving data to/from a relational database. The decision of which repositories are employed, as well as the location of the repository input files / database will be made available via the program’s **settings.properties** file and the Java *Properties* class. See an example is below:

> Repository = database \
> Location = data \
> Patients = patients \
> Appointments = appointments

-	Provide various reports, using Java 8 streams. You should create at least 5 different reports. See some examples below:

    o	all the appointments for a certain patient (and their status); \
    o	the problems of a certain patient; \
    o	the phone number of a certain patient (given by id); \
    o	the name of the persons who booked a certain car; \
    o	all cars rented by a certain person; \
    o	the list of birthday cakes that for ordered for a given day; \
    o	the days when a certain birthday cake has to be delivered.


**Bonus (0.2p)** \
Allow storing/retrieving your data to/from JSON (**0.2p**) and XML (**0.2p**) files. The decision of which type of file to use and the necessary paths are given in the same configuration file (the program’s **settings.properties** file).
