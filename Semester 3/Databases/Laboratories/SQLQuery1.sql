CREATE TABLE OwnerBooking (
	Oid int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	OName varchar(50)
)

CREATE TABLE Client (
	Cid int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	CName varchar(50) NOT NULL,
	Email NVARCHAR(100)
)

CREATE TABLE Languages (
	Lid int NOT NULL PRIMARY KEY,
	LName varchar(50) NOT NULL,
)

CREATE TABLE LanguagesSpokenByOwner (
	Lid int NOT NULL,
	Oid int NOT NULL,
	CONSTRAINT FK_LanguagesSpokenByOwner_Language FOREIGN KEY (Lid) REFERENCES Languages(Lid),
    CONSTRAINT FK_LanguagesSpokenByOwner_Owner FOREIGN KEY (Oid) REFERENCES OwnerBooking(Oid)
)

CREATE TABLE LanguagesSpokenByClient (
	Lid int NOT NULL,
	Cid int NOT NULL,
	CONSTRAINT FK_LanguagesSpokenByClient_Language FOREIGN KEY (Lid) REFERENCES Languages(Lid),
    CONSTRAINT FK_LanguagesSpokenByClient_Client FOREIGN KEY (Cid) REFERENCES Client(Cid)
)

CREATE TABLE Payment(
	id smallint IDENTITY(1,1) NOT NULL PRIMARY KEY,
	method varchar(50) CHECK (method IN ('CASH','CARD')),
	payment_date date
)


CREATE TABLE Booking (
	Bid int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	LocationName varchar(50) NOT NULL,
	Capacity int,
	Oid int FOREIGN KEY REFERENCES OwnerBooking(Oid) UNIQUE,
	Cid int FOREIGN KEY REFERENCES Client(Cid) UNIQUE,
	paymentID smallint FOREIGN KEY REFERENCES Payment(id)
)
