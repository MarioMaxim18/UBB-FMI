CREATE FUNCTION validateLanguageName(@name VARCHAR(50))
RETURNS BIT AS 
BEGIN
    DECLARE @isValid BIT
    IF @name LIKE '[A-Z]%'
        SET @isValid = 1
    ELSE
        SET @isValid = 0
    RETURN @isValid
END
GO

CREATE PROCEDURE insertLanguageSpokenByOwner
    @LName VARCHAR(50),
    @Oid INT
AS
BEGIN
    IF dbo.validateLanguageName(@LName) = 1
    BEGIN
        DECLARE @Lid INT
        
        SELECT @Lid = Lid FROM Languages WHERE LName = @LName
        
        IF @Lid IS NULL
        BEGIN
            PRINT 'Language not found.'
        END
        ELSE
        BEGIN
            INSERT INTO LanguagesSpokenByOwner (Lid, Oid)
            VALUES (@Lid, @Oid)
            
            PRINT 'Record successfully added!'
            SELECT * FROM LanguagesSpokenByOwner
        END
    END
    ELSE
    BEGIN
        PRINT 'Validation failed. Check the inputs.'
    END
END
GO

EXEC insertLanguageSpokenByOwner @LName = 'Romanian', @Oid = 1  -- Valid
EXEC insertLanguageSpokenByOwner @LName = 'French', @Oid = 1  --  Language not found

CREATE VIEW vBookingDetails AS
SELECT 
    b.Bid, 
    o.OName AS OwnerName, 
    c.CName AS ClientName, 
    l.LName AS ClientLanguage, 
    b.LocationName AS Name, 
    b.Capacity, 
    p.method AS PaymentMethod, 
    p.payment_date AS PaymentDate
FROM 
    Booking b
INNER JOIN 
    OwnerBooking o ON b.Oid = o.Oid
INNER JOIN 
    Client c ON b.Cid = c.Cid
INNER JOIN 
    LanguagesSpokenByClient lsc ON c.Cid = lsc.Cid
INNER JOIN 
    Languages l ON lsc.Lid = l.Lid
INNER JOIN 
    Payment p ON b.paymentID = p.id;

SELECT * FROM vBookingDetails;
    
CREATE TABLE Logs (
LogID INT IDENTITY(1,1) PRIMARY KEY,
TriggerDate DATETIME DEFAULT GETDATE(),
TriggerType VARCHAR(10),    -- INSERT, UPDATE, DELETE
NameAffectedTable VARCHAR(50),
NoAMDRows INT
);

CREATE TABLE BookingCopy (
    Bid INT PRIMARY KEY,
    LocationName VARCHAR(50) NOT NULL,
    Capacity INT,
    Oid INT,
    Cid INT,
    paymentID SMALLINT
);

CREATE TRIGGER Insert_Booking ON Booking FOR 
INSERT AS
BEGIN
    INSERT INTO BookingCopy (Bid, LocationName, Capacity, Oid, Cid, paymentID)
    SELECT Bid, LocationName, Capacity, Oid, Cid, paymentID
    FROM inserted;

    
    INSERT INTO Logs (TriggerDate, TriggerType, NameAffectedTable, NoAMDRows)
    VALUES (GETDATE(), 'INSERT', 'Booking', @@ROWCOUNT);
END;

SELECT * FROM Booking;
SELECT * FROM BookingCopy;
INSERT INTO Booking (LocationName, Capacity, Oid, Cid, paymentID) VALUES ('Hotel Bucharest', 150, 3, 20, 1);
SELECT * FROM Booking;
SELECT * FROM BookingCopy;
SELECT * FROM Logs;

CREATE TRIGGER Update_Booking ON Booking FOR 
UPDATE AS
BEGIN
    INSERT INTO Logs (TriggerDate, TriggerType, NameAffectedTable, NoAMDRows)
    VALUES (GETDATE(), 'UPDATE', 'Booking', @@ROWCOUNT);
END;

CREATE TRIGGER Delete_Booking ON Booking FOR 
DELETE AS
BEGIN
    INSERT INTO Logs (TriggerDate, TriggerType, NameAffectedTable, NoAMDRows)
    VALUES (GETDATE(), 'DELETE', 'Booking', @@ROWCOUNT);
END;

UPDATE Booking 
SET Capacity = 200 
WHERE LocationName = 'Hotel Bucharest';

SELECT * FROM Booking;
SELECT * FROM BookingCopy;
SELECT * FROM Logs;

DELETE FROM Booking 
WHERE LocationName = 'Hotel Bucharest';

SELECT * FROM Booking;
SELECT * FROM BookingCopy;
SELECT * FROM Logs;

CREATE NONCLUSTERED INDEX idx_LocationName ON Booking (LocationName);
CREATE NONCLUSTERED INDEX idx_OName ON OwnerBooking (OName);

SELECT b.Bid, b.LocationName, o.OName 
FROM Booking b 
JOIN OwnerBooking o ON b.Oid = o.Oid 
WHERE b.LocationName LIKE 'H%' 
ORDER BY b.Bid;

