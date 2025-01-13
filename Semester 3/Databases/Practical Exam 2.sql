CREATE TABLE Customers(
	id int PRIMARY KEY,
	firstName varchar(50),
	lastName varchar(50),
	date date
);

CREATE TABLE Products(
	id int PRIMARY KEY,
	name varchar(50),
	price int,
	categoryID  int,
	FOREIGN KEY(categoryID) REFERENCES Category(id)
);

CREATE TABLE Category(
	id int PRIMARY KEY,
	name varchar(50)
);

CREATE TABLE Orders(
	date date,
	quantity int,
	totalPrice int,
	customerID int,
	productID int,
	PRIMARY KEY(customerID, productID),
	FOREIGN KEY(customerID) REFERENCES Customers(id),
	FOREIGN KEY(productID) REFERENCES Products(id)
);

GO
CREATE TRIGGER UpdateTotalPrice
ON Orders
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;
    UPDATE Orders
    SET totalPrice = i.quantity * p.price
    FROM Orders o
    INNER JOIN INSERTED i ON o.customerID = i.customerID AND o.productID = i.productID
    INNER JOIN Products p ON i.productID = p.id;
END;
GO

INSERT INTO Category (id, name) VALUES 
    (1, 'Electronics'),
    (2, 'Books'),
    (3, 'Clothing');

INSERT INTO Products (id, name, price, categoryID) VALUES 
    (1, 'Laptop', 1000, 1),
    (2, 'Smartphone', 700, 1),
    (3, 'Fiction Book', 20, 2),
    (4, 'T-shirt', 15, 3);


INSERT INTO Customers (id, firstName, lastName, date) VALUES 
    (1, 'c1', 'A', '2025-01-01'),
    (2, 'c2', 'B', '2025-01-02'),
    (3, 'c2', 'C', '2025-01-03');

INSERT INTO Orders (date, quantity, totalPrice, customerID, productID) VALUES 
    ('2025-01-10', 2, 0, 1, 1), 
    ('2025-01-11', 1, 0, 2, 2), 
    ('2025-01-12', 5, 0, 3, 3);


GO
CREATE OR ALTER PROCEDURE addOrder(@date date, @quantity int, @totalPrice int, @customer int, @product int) AS 
BEGIN
	IF EXISTS(
		SELECT 1
		FROM Orders WHERE customerID = @customer and productID = @product
	)
	BEGIN
		UPDATE Orders
		SET date = @date, quantity = @quantity
		WHERE customerID = @customer and productID = @product
		RETURN
	END
	INSERT INTO Orders(date, quantity, totalPrice, customerID, productID) VALUES (@date, @quantity, @totalPrice, @customer, @product)
END

EXEC addOrder '2025-01-13', 5, 0, 1, 2
EXEC addOrder '2025-01-13', 8, 0, 3, 1
SELECT * FROM Orders

GO
CREATE OR ALTER VIEW customerThatSpentMoreThanAverageTotalPrice AS
	SELECT c.id, c.firstName, c.lastName FROM Customers c
	INNER JOIN Orders o ON o.customerID = c.id
	GROUP BY c.id, c.firstName, c.lastName
	HAVING SUM(o.totalPrice) > (SELECT AVG(totalPrice) FROM Orders)

GO
SELECT * FROM customerThatSpentMoreThanAverageTotalPrice

GO
CREATE OR ALTER FUNCTION categoriesWithProducts(@N int)
RETURNS TABLE
AS
RETURN
	SELECT c.id, c.name as Name FROM Category c
	INNER JOIN Products p ON p.categoryID = c.id
	GROUP BY c.id, c.name
	HAVING COUNT(DISTINCT p.id) >= @N

GO
SELECT * FROM categoriesWithProducts(2)