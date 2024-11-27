--ADD/REMOVE A COLUMN
-- ADD 'phone'
CREATE OR ALTER PROCEDURE AddPhoneColumn AS
    ALTER TABLE Client
    ADD phone VARCHAR(15);
GO
EXECUTE AddPhoneColumn
GO

-- REMOVE 'phone' 
CREATE OR ALTER PROCEDURE RemovePhoneColumn AS
    ALTER TABLE Client
    DROP COLUMN phone;
GO
EXECUTE RemovePhoneColumn
GO

--ADD/REMOVE A DEFAULT CONSTRAINT
--ADD
CREATE OR ALTER PROCEDURE AddDefaultPaymentDate AS
    ALTER TABLE Payment
		ADD CONSTRAINT DF_payment_date DEFAULT GETDATE() FOR payment_date;
GO
EXECUTE AddDefaultPaymentDate
GO

--REMOVE
CREATE OR ALTER PROCEDURE RemoveDefaultPaymentDate AS
    ALTER TABLE Payment
    DROP CONSTRAINT DF_payment_date;
GO
EXECUTE RemoveDefaultPaymentDate
GO

--CREATE/DROP TABLE
CREATE OR ALTER PROCEDURE CreateTableFeedback AS
	CREATE TABLE Feedback (
		id INT IDENTITY(1,1) PRIMARY KEY,
		clientID INT FOREIGN KEY REFERENCES Client(Cid),
		feedbackText VARCHAR(250)
	);
GO
EXECUTE CreateTableFeedback
GO

CREATE OR ALTER PROCEDURE DropTableFeedBack AS
	DROP TABLE Feedback
GO
EXECUTE DropTableFeedBack
GO

--ADD/REMOVE A FOREIGN KEY
CREATE OR ALTER PROCEDURE RemoveForeignKey
AS
    ALTER TABLE Booking
    DROP CONSTRAINT FK_Booking_PaymentID;
GO
EXECUTE RemoveForeignKey
GO	

CREATE OR ALTER PROCEDURE AddForeignKey AS
	ALTER TABLE Booking
		ADD CONSTRAINT FK_Booking_PaymentID
		FOREIGN KEY (paymentID) REFERENCES Payment(id);
GO
EXECUTE AddForeignKey
GO

CREATE TABLE VersionTable
(
	Version INT
)

INSERT INTO VersionTable VALUES (1)

CREATE TABLE ProcedureTable(
	FirstVersion int,
	LastVersion int,
	ProcedureName varchar(50),
	PRIMARY KEY(Firstversion,LastVersion)
)

INSERT INTO ProcedureTable VALUES(1,2 , 'AddPhoneColumn')
INSERT INTO ProcedureTable VALUES(2,1 , 'RemovePhoneColumn')
INSERT INTO ProcedureTable VALUES(2,3 , 'AddDefaultPaymentDate')
INSERT INTO ProcedureTable VALUES(3,2 , 'RemoveDefaultPaymentDate')
INSERT INTO ProcedureTable VALUES(3,4 , 'CreateTableFeedback')
INSERT INTO ProcedureTable VALUES(4,3 , 'DropTableFeedBack')
INSERT INTO ProcedureTable VALUES(4,5, 'AddForeignKey')
INSERT INTO ProcedureTable VALUES(5,6, 'RemoveForeignKey')

CREATE OR ALTER PROCEDURE restoreVersion(@version INT) AS
    DECLARE @currentVersion INT
    DECLARE @procedureName VARCHAR(MAX)
    SELECT @currentVersion = Version FROM VersionTable
 
    WHILE @currentVersion > @version BEGIN
        SELECT @procedureName = ProcedureName FROM ProcedureTable 
			WHERE FirstVersion = @currentVersion AND LastVersion = @currentVersion-1
        EXEC (@procedureName)
        SET @currentVersion = @currentVersion-1
    END
 
    WHILE @currentVersion < @version BEGIN
        SELECT @procedureName = ProcedureName 
		FROM ProcedureTable 
		WHERE FirstVersion = @currentVersion AND LastVersion = @currentVersion+1
	    EXEC (@procedureName)
        SET @currentVersion = @currentVersion+1
    END
 
    UPDATE VersionTable SET Version = @version
    RETURN
 
EXECUTE restoreVersion 4