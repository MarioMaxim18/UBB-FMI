USE Booking;

INSERT INTO Languages(Lid,LName) VALUES (1,'Romanian');
INSERT INTO Languages(Lid,LName) VALUES (2,'Italian');
INSERT INTO Languages(Lid,LName) VALUES (3,'German');
INSERT INTO Languages(Lid,LName) VALUES (4,'Mandarin');
INSERT INTO Languages(Lid,LName) VALUES (5,'Arabic');
INSERT INTO Languages(Lid,LName) VALUES (6,'Arabic');

--update
UPDATE Languages SET LName = 'Romanian' WHERE Lid BETWEEN 1 AND 2
--delete because data is duplicated
DELETE FROM Languages WHERE LName = 'Arabic' AND Lid >5;
SELECT * FROM Languages;

INSERT INTO OwnerBooking(Oname) VALUES ('Ioan');
INSERT INTO OwnerBooking(Oname) VALUES ('Vasile');
INSERT INTO OwnerBooking(Oname) VALUES ('Iosif');
INSERT INTO OwnerBooking(Oname) VALUES ('Maria');
INSERT INTO OwnerBooking(Oname) VALUES('LORENA');
INSERT INTO OwnerBooking(Oname) VALUES('Iosid');

--Delete because mistyped name
DELETE FROM OwnerBooking WHERE Oname like 'L%';
DELETE FROM OwnerBooking WHERE Oname='Iosid';
SELECT * FROM OwnerBooking;

SELECT "Oname" AS Owners_Desc FROM OwnerBooking 
ORDER BY "Oname" DESC

INSERT INTO Client(CName , Email) VALUES('Magdalena','magdalena123@yahoo.com');
INSERT INTO Client(CName , Email) VALUES('Ioana','ioana.io@gmail.com');
INSERT INTO Client(CName , Email) VALUES('Laurentiu','laurentiu-andrei@yahoo.com');
INSERT INTO Client(CName , Email) VALUES('Vasile','vasile1999@gmail.com');
INSERT INTO Client(CName , Email) VALUES('mariana','mariana__$@gmail.com');

UPDATE Client SET Cname='Mariana' WHERE CName like 'mariana';
SELECT * FROM Client;

INSERT INTO LanguagesSpokenByClient(Lid,Cid) VALUES (1,18);
INSERT INTO LanguagesSpokenByClient(Lid,Cid) VALUES (1,19);
INSERT INTO LanguagesSpokenByClient(Lid,Cid) VALUES (2,20);
INSERT INTO LanguagesSpokenByClient(Lid,Cid) VALUES (3,21);
INSERT INTO LanguagesSpokenByClient(Lid,Cid) VALUES (5,22);

SELECT * FROM LanguagesSpokenByClient;

INSERT INTO LanguagesSpokenByOwner(Lid,Oid) VALUES (1,1);
INSERT INTO LanguagesSpokenByOwner(Lid,Oid) VALUES (1,2);
INSERT INTO LanguagesSpokenByOwner(Lid,Oid) VALUES (2,3);
INSERT INTO LanguagesSpokenByOwner(Lid,Oid) VALUES (3,4);
INSERT INTO LanguagesSpokenByOwner(Lid,Oid) VALUES (5,5);

SELECT * FROM LanguagesSpokenByOwner;

INSERT INTO Booking(LocationName,Capacity,Oid,Cid) VALUES ('Italy',4,1,18)
INSERT INTO Booking(LocationName,Capacity,Oid,Cid) VALUES ('Spain',2,3,19)
INSERT INTO Booking(LocationName,Capacity,Oid,Cid) VALUES ('Romania',2,4,21);
INSERT INTO Booking(LocationName,Capacity,Oid,Cid) VALUES ('Spania' ,2,5,22);

UPDATE Booking SET LocationName = 'Spain' WHERE LocationName = 'Spania'
SELECT * FROM Booking

SELECT * FROM Booking 
INNER JOIN OwnerBooking ON Booking.Oid = OwnerBooking.Oid
INNER JOIN Client ON Booking.Cid = Client.Cid;

SELECT * FROM OwnerBooking
LEFT JOIN Booking ON OwnerBooking.Oid = Booking.Oid;

SELECT * FROM Booking
RIGHT JOIN Client ON Booking.Cid = Client.Cid

--Display all the languages info spoken by client and owner ,and also client's and owner's info
SELECT *
FROM LanguagesSpokenByOwner AS LSO
INNER JOIN Languages AS L ON L.Lid = LSO.Lid
INNER JOIN OwnerBooking AS OB ON LSO.Oid = OB.Oid
FULL JOIN (
    SELECT LSC.Lid, LSC.Cid, C.Email -- Lid and Cid are present in multiple tables, causing ambiguity.
    FROM LanguagesSpokenByClient AS LSC
    INNER JOIN Languages AS L2 ON L2.Lid = LSC.Lid
    INNER JOIN Client AS C ON LSC.Cid = C.Cid
) AS ClientLanguages ON LSO.Lid = ClientLanguages.Lid;

--Display all the DISTINCT names from every Client and Owner, UNION==>duplicates won t show
SELECT Cname FROM Client
UNION
SELECT Oname FROM OwnerBooking

--Display mutual names between client and ownerBooking
SELECT CName FROM Client
INTERSECT
SELECT OName FROM OwnerBooking

--Select langauges which are also spoken by client and have the id > 1
SELECT Lid , Lname  FROM Languages
where Lid IN(
	SELECT Lid FROM LanguagesSpokenByClient
	WHERE Lid > 1
);

SELECT Oid , Lid FROM LanguagesSpokenByOwner;

SELECT Lid , Lname FROM Languages
where Lid NOT IN(
	SELECT Lid FROM LanguagesSpokenByOwner
	WHERE Lid > 1
);

SELECT * FROM Booking
EXCEPT(
	SELECT * FROM Booking
	WHERE Booking.LocationName = 'Spain' OR Booking.capacity > 2
);

SELECT * FROM Client
WHERE Cid IN(
	SELECT Cid FROM Booking 
	WHERE Cid IN(
		SELECT Cid FROM LanguagesSpokenByClient
	)
)

--Displays the owners which speaks the same lanuage as at least one client
SELECT Oid,Lid FROM LanguagesSpokenByOwner
WHERE EXISTS(
	SELECT Lid FROM LanguagesSpokenByClient 
	WHERE Lid < 3 AND LanguagesSpokenByClient.Lid = LanguagesSpokenByOwner.Lid
)

--Displays the Client which speaks at least one language
SELECT * FROM Client
WHERE EXISTS(
	SELECT Cid FROM LanguagesSpokenByClient
	WHERE Cid = Client.Cid
)

SELECT * FROM Booking B INNER JOIN(
	SELECT Cname,email,Cid FROM Client C
	WHERE email LIKE '%gmail.com' AND CName LIKE 'I%'
)AS ClientsWithYahoo ON B.Cid = ClientsWithYahoo.Cid; 

SELECT * FROM Booking B INNER JOIN(
	SELECT Oname,Oid FROM OwnerBooking O
	WHERE Oname LIKE 'i%'
)AS OwnersStartingI ON B.Oid = OwnersStartingI.Oid;

--Displays the number of languages each client speaks , if speaks more than 1 language
SELECT Cid, COUNT(Lid) AS TotalLanguages
FROM LanguagesSpokenByClient
GROUP BY Cid
HAVING COUNT(Lid) > 0;  


--Displays the top 2 owners which speaks as many languages as possible and more than 1 language
SELECT TOP 2 Oid, COUNT(Lid) AS TotalLanguages
FROM LanguagesSpokenByOwner
GROUP BY Oid
HAVING COUNT(Lid) > 0
ORDER BY COUNT(Lid) DESC;

--Displays the number of bookings every owner has
SELECT Oid, COUNT(*) AS TotalBookings
FROM Booking
GROUP BY Oid;

--Displays the max and min capacity descending from each location
SELECT TOP 2 LocationName, MIN(capacity) AS MinCapacity, MAX(capacity) AS MaxCapacity
FROM Booking
GROUP BY LocationName
ORDER BY MaxCapacity DESC;

SELECT DISTINCT capacity FROM Booking;