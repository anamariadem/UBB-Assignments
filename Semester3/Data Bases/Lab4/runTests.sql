  
CREATE PROCEDURE addTest @testName VARCHAR(50)
AS
BEGIN
	IF @testName NOT IN (SELECT Name FROM Tests)
	BEGIN
		INSERT Tests(Name) VALUES (@testName)
	END
	ELSE 
		PRINT 'A test with ' + @testName + ' already exists!'
END
go


CREATE PROCEDURE addTable @tableName VARCHAR(50)
AS
BEGIN
	IF @tableName NOT IN (SELECT Name FROM Tables)
	BEGIN
		INSERT Tables(Name) VALUES (@tableName)
	END
	ELSE
		PRINT 'A table with name ' + @tableName + ' was already added!'
END
go

CREATE PROCEDURE addEntryInTestTables @testName VARCHAR(50), @tableName VARCHAR(50), @noOfRows INT, @position INT
AS
BEGIN
	DECLARE @testId INT, @tableID INT
	SET @testId = (SELECT TestID FROM Tests WHERE Name = @testName)
	SET @tableID = (SELECT TableID FROM Tables WHERE Name = @tableName)

	IF @testId IS NULL
	BEGIN
		PRINT 'There is no test with id: ' + @testId
		RETURN
	END

	IF @tableId IS NULL
	BEGIN
		PRINT 'There is no table with id: ' + @tableId
		RETURN
	END

	INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) 
		VALUES (@testId, @tableID, @noOfRows, @position)

END
GO 

EXEC addTest 'test1'
EXEC addTable 'Player'
EXEC addEntryInTestTables 'test1', 'Player', 30, 3

SELECT * FROM Tests
SELECT * FROM Tables
SELECT * FROM TestTables

DELETE FROM TestTables
DELETE FROM Tables
DELETE FROM Tests
DBCC CHECKIDENT (Tests, RESEED, 0)
DBCC CHECKIDENT (Tables, RESEED, 0)
GO

CREATE PROCEDURE addView @viewName VARCHAR(50) 
AS 
BEGIN
	IF @viewName NOT IN (SELECT Name FROM Views)
	BEGIN
		INSERT Views(Name) VALUES (@viewName)
	END
	ELSE
		PRINT 'A view with name ' + @viewName + ' was already added!'
END
GO

CREATE PROCEDURE addEntryInTestViews @testName VARCHAR(50), @viewName VARCHAR(50)
AS
BEGIN
	DECLARE @testId INT, @viewID INT
	SET @testId = (SELECT TestID FROM Tests WHERE Name = @testName)
	SET @viewID = (SELECT ViewID FROM Views WHERE Name = @viewName)

	IF @testId IS NULL
	BEGIN
		PRINT 'There is no test with id: ' + @testId
		RETURN
	END

	IF @viewId IS NULL
	BEGIN
		PRINT 'There is no view with id: ' + @viewId
		RETURN
	END

	INSERT INTO TestViews(TestID, ViewID) 
		VALUES (@testId, @viewID)
END
GO

CREATE VIEW GrandSlamWinners
AS
	SELECT Player.FirstName, Player.LastName
	FROM Player 
	WHERE PlayerId IN(
		SELECT PlayerId
		FROM TournamentWinner
		WHERE TournamentId IN (
			SELECT TournamentId
			FROM Tournament
			WHERE TTYPE = 'Grand Slam'
		)
)
GO

CREATE VIEW PlayersWithAtLeast2000Points
AS
	SELECT FirstName, LastName 
	FROM Player
	WHERE NumberOfPoints > 2000
GO

CREATE VIEW AverageSalariesCoachUmpire
AS
	SELECT U.UType, AVG(U.MonthlyIncome) AS "Average Salary"
	FROM Umpire U
	GROUP BY U.UType
	HAVING  AVG(U.MonthlyIncome) > (
		SELECT AVG(C.MonthlyIncome) 
		FROM Coach C
	)
GO

EXEC addTest 'test2'
EXEC addView 'GrandSlamWinners'
EXEC addEntryInTestViews 'test2', 'GrandSlamWinners'

SELECT * FROM Tests
SELECT * FROM Views
SELECT * FROM TestViews
DBCC CHECKIDENT (Views, RESEED, 0)
DBCC CHECKIDENT (TestViews,  RESEED, 0)
GO

CREATE PROCEDURE runTest @testName VARCHAR(50)
AS
BEGIN
	DECLARE @testId INT
	SET @testId = (SELECT TestID FROM Tests WHERE Name = @testName)

	IF @testId IS NULL
	BEGIN
		PRINT 'Test with id ' + @testId  +' does not exist!' 
		RETURN
	END

	DECLARE TablesCursor CURSOR SCROLL FOR
		SELECT T.TableID, T.Name, TT.NoOfRows, TT.Position
		FROM Tables T INNER JOIN TestTables TT ON T.TableID = TT.TableID
		WHERE TT.TestID = @testId
		ORDER BY TT.Position

	DECLARE ViewsCursor CURSOR SCROLL FOR
		SELECT V.ViewID, V.Name
		FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
		WHERE TV.TestID = @testId

	SET NOCOUNT ON

	INSERT INTO TestRuns(Description) VALUES
		('Test runs for test: ' + @testName)

	DECLARE @tableId INT, @numberOfRows INT, @position INT, @tableName VARCHAR(50),
		@viewId INT, @viewName VARCHAR(50), @globalStartTime DATETIME2, @globalEndTime DATETIME2

	DECLARE @testRunId INT
	SET @testRunId = CONVERT(INT, (SELECT last_value 
									FROM SYS.identity_columns 
									WHERE name = 'TestRunID'))

	SET @globalStartTime = SYSDATETIME()

	--delete data from testtables in order specified by the position
	OPEN TablesCursor
	FETCH FIRST FROM TablesCursor
	INTO @tableId, @tableName, @numberOfRows, @position

	DECLARE @commandToExecute VARCHAR(50)

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @commandToExecute = 'DELETE FROM ' + @tableName
		EXEC(@commandToExecute)
		PRINT 'EXECUTING ' + @commandToExecute + ' .....'

		FETCH NEXT FROM TablesCursor
		INTO @tableId, @tableName, @numberOfRows, @position
	END

	CLOSE TablesCursor


	DECLARE @insertStartTime DATETIME2, @insertEndTime DATETIME2
	--insert data in test tables in the reverse order specified by the position
	OPEN TablesCursor
	FETCH LAST FROM TablesCursor
	INTO @tableId, @tableName, @numberOfRows, @position

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @commandToExecute = 'populateTable ''' + @tableName + ''', '+ CONVERT(VARCHAR(7), @numberOfRows)

		SET @insertStartTime = SYSDATETIME()
		EXEC(@commandToexecute)
		PRINT 'EXECUTING ' + @commandToExecute + ' .....'
		SET @insertEndTime = SYSDATETIME()

		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES
			(@testRunId, @tableId, @insertStartTime, @insertEndTime)

		FETCH PRIOR FROM TablesCursor
		INTO @tableId, @tableName, @numberOfRows, @position
	END

	CLOSE TablesCursor

	DECLARE @selectStartTime DATETIME2, @selectEndTime DATETIME2
	--test the views
	OPEN ViewsCursor
	FETCH FIRST FROM ViewsCursor
	INTO @viewId, @viewName

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @commandToExecute = 'SELECT * FROM ' + @viewName

		SET @selectStartTime = SYSDATETIME()
		EXEC (@commandToExecute)
		PRINT 'EXECUTING ' + @commandToExecute + ' .....'
		SET @selectEndTime = SYSDATETIME()

		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES
			(@testRunId, @viewId, @selectStartTime, @selectEndTime)

			FETCH NEXT FROM ViewsCursor
			INTO @viewId, @viewName
	END
	CLOSE ViewsCursor

	SET @globalEndTime = SYSDATETIME()

	--update the test runs table
	UPDATE TestRuns
	SET StartAt = @globalStartTime, EndAt = @globalEndTime
	WHERE TestRunID = @testRunId

	
	DEALLOCATE TablesCursor
	DEALLOCATE ViewsCursor
END
GO

CREATE PROCEDURE showTestResults @testName VARCHAR(50)
AS
BEGIN
	SELECT * 
	FROM TestRuns
	WHERE Description LIKE '%' + @testName + '%'

	SELECT T.Name, TRT.StartAt, TRT.EndAt
	FROM Tables T INNER JOIN TestRunTables TRT ON T.TableID = TRT.TableID
	WHERE TRT.TestRunID IN (
		SELECT TestRunID
		FROM TestRuns
		WHERE Description LIKE '%' + @testName + '%'
	)

	SELECT V.Name, TRV.StartAt, TRV.EndAt
	FROM Views V INNER JOIN TestRunViews TRV ON V.ViewID = TRV.ViewID
	WHERE TRV.TestRunID IN (
		SELECT TestRunID
		FROM TestRuns
		WHERE Description LIKE '%' + @testName + '%'
	)


END
GO

DROP PROCEDURE runTest

SELECT * FROM Tests
SELECT * FROM Tables
SELECT * FROM TestTables
SELECT * FROM Views
SELECT* FROM TestViews

EXEC addTable 'Sponsor'
EXEC addTable 'Player_Sponsor'
EXEC addTable 'Coach'

EXEC addEntryInTestTables 'test1', 'Player', 30, 4
EXEC addEntryInTestTables 'test1', 'Coach', 5, 3
EXEC addEntryInTestTables 'test1', 'Sponsor', 10, 2
EXEC addEntryInTestTables 'test1', 'Player_Sponsor', 5, 1


EXEC addTest 'test3'
EXEC addEntryInTestTables 'test3', 'Player', 1000, 4
EXEC addEntryInTestTables 'test3', 'Coach', 100, 3
EXEC addEntryInTestTables 'test3', 'Sponsor', 50, 2
EXEC addEntryInTestTables 'test3', 'Player_Sponsor', 75, 1


EXEC runTest 'test1'
EXEC runTest 'test3'

SELECT * FROM Player
SELECT * FROM Sponsor
SELECT * FROM Player_Sponsor

DELETE FROM TestRuns
DBCC CHECKIDENT (TestRuns,  RESEED, 0)
DELETE FROM TestRunTables

DELETE FROM TestTables
DBCC CHECKIDENT (TestTables,  RESEED, 0)

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

SELECT * FROM Player
SELECT * FROM Sponsor
SELECT * FROM Coach
SELECT * FROM Player_Sponsor

EXEC addView 'PlayersWithAtLeast2000Points'
EXEC addEntryInTestViews 'test2', 'PlayersWithAtLeast2000Points'

EXEC addView 'AverageSalariesCoachUmpire'
EXEC addEntryInTestViews 'test2', 'AverageSalariesCoachUmpire'

EXEC runTest 'test2'
SELECT * FROM TestRuns
SELECT * FROM TestRunViews

EXEC showTestResults 'test1'
EXEC showTestResults 'test3'