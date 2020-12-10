USE ATPDB
GO;

--a. modify the type of a column
CREATE PROCEDURE ModifyTypeOfTennisRacketPrice
AS
	ALTER TABLE TennisRacket
	ALTER COLUMN Price FLOAT
GO

CREATE PROCEDURE ReverseModifyTypeOfTennisRacketPrice
AS
	ALTER TABLE TennisRacket
	ALTER COLUMN Price INT
GO


-- b. add / remove a column;
CREATE PROCEDURE AddUmpireAgeColumn
AS
	ALTER TABLE Umpire
	ADD UAge SMALLINT
GO

CREATE PROCEDURE RemoveUmpireAgeColumn
AS
	ALTER TABLE Umpire
	DROP COLUMN UAge
GO

EXEC AddUmpireAgeColumn
GO

EXEC RemoveUmpireAgeColumn
GO

--c. add / remove a DEFAULT constraint;
CREATE PROCEDURE AddDefaultSallaryForCoach
AS
	ALTER TABLE Coach
	ADD CONSTRAINT df_Income
	DEFAULT 500 FOR MonthlyIncome
GO

CREATE PROCEDURE RemoveDefaultSalaryForCoach
AS
	ALTER TABLE Coach
	DROP CONSTRAINT df_Income
GO

EXEC AddDefaultSallaryForCoach
GO

EXEC RemoveDefaultSalaryForCoach
GO

CREATE PROCEDURE AddDefaultWeightForRacket
AS
	ALTER TABLE TennisRacket
	ADD CONSTRAINT df_Weight
	DEFAULT 250 FOR RacketWeight
GO

CREATE PROCEDURE RemoveDefaultWeightForRacket
AS
	ALTER TABLE TennisRacket
	DROP CONSTRAINT df_Weight
GO

--d. add / remove a primary key
CREATE PROCEDURE AddTennisRacketPrimaryKey
AS
	ALTER TABLE TennisRacket
	ADD CONSTRAINT Pk_TennisRacket PRIMARY KEY (RacketId)
GO

CREATE PROCEDURE RemoveTennisRacketPrimaryKey
AS
	ALTER TABLE Tennisracket
	DROP CONSTRAINT Pk_TennisRacket
GO

EXEC AddTennisRacketPrimaryKey
GO

EXEC RemoveTennisRacketPrimaryKey
GO

drop procedure RemoveTennisRacketPrimaryKey

-- e. add / remove a candidate key

CREATE PROCEDURE AddPlayerCandidateKey
AS
	ALTER TABLE Player
	ADD CONSTRAINT Ck_Player UNIQUE(PlayerId, FirstName, LastName, NumberOfPoints)
GO

CREATE PROCEDURE RemovePlayerCandidateKey
AS
	ALTER TABLE Player
	DROP CONSTRAINT Ck_Player
GO

CREATE PROCEDURE AddTennisRacketCandidateKey
AS
	ALTER TABLE TennisRacket
	ADD CONSTRAINT Ck_TennisRacket UNIQUE(RacketId)
GO

CREATE PROCEDURE RemoveTennisRacketCandidateKey
AS
	ALTER TABLE TennisRacket
	DROP CONSTRAINT Ck_TennisRacket
GO


drop procedure RemoveTennisRacketCandidateKey
-- f. add / remove a foreign key
CREATE PROCEDURE AddTennisRacketForeignKey
AS
	 ALTER TABLE TennisRacket
	 ADD PlayerId INT

	 ALTER TABLE TennisRacket
	 ADD CONSTRAINT FK_Pid
	 FOREIGN KEY (PlayerId) REFERENCES Player(PlayerId)
go

CREATE PROCEDURE RemoveTennisRacketForeignKey
AS
	ALTER TABLE TennisRacket
	DROP CONSTRAINT FK_Pid

	ALTER TABLE TennisRacket
	DROP COLUMN PlayerId
GO

EXEC AddTennisRacketForeignKey
GO

drop procedure AddTennisRacketForeignKey
drop procedure RemoveTennisRacketForeignKey

EXEC RemoveTennisRacketForeignKey
GO

drop procedure RemoveTennisRacketForeignKey


--g. create / drop a table.
CREATE PROCEDURE CreateTableTennisRacket
AS 
	CREATE TABLE TennisRacket
	(RacketId INT NOT NULL,
	Brand VARCHAR(50) NOT NULL,
	Price INT,
	RacketWeight INT NOT NULL)
	--PlayerId INT REFERENCES Player(PlayerId))
GO;

drop procedure CreateTableTennisRacket

CREATE PROCEDURE DropTableTennisRacket
AS 
	DROP TABLE TennisRacket
GO;

EXEC CreateTableTennisRacket;
GO;


EXEC DropTableTennisRacket;
GO;

CREATE TABLE CurrentVersion 
(
	CurrentVersion INT default  0
)

INSERT CurrentVersion(CurrentVersion) 
VALUES (0)

SELECT * FROM CurrentVersion

UPDATE CurrentVersion
SET CurrentVersion = CurrentVersion - 1

CREATE TABLE Procedures_Versions(
	DoProcedure VARCHAR(50),
	UndoProcedure VARCHAR(50),
	CorrespondingVersion INT
)

INSERT Procedures_Versions(DoProcedure, UndoProcedure, CorrespondingVersion) VALUES
	('CreateTableTennisRacket','DropTableTennisRacket', 1 ) --g

INSERT Procedures_Versions(DoProcedure, UndoProcedure, CorrespondingVersion) VALUES
	('AddTennisRacketCandidateKey', 'RemoveTennisRacketCandidateKey', 2), --e
	('AddTennisRacketPrimaryKey', 'RemoveTennisRacketPrimaryKey', 3), --d
	('AddTennisRacketForeignKey', 'RemoveTennisRacketForeignKey', 4), --f
	('AddUmpireAgeColumn', 'RemoveUmpireAgeColumn', 5), --b
	('ModifyTypeOfTennisRacketPrice', 'ReverseModifyTypeOfTennisRacketPrice', 6), --a
	('AddDefaultWeightForRacket', 'RemoveDefaultWeightForRacket', 7) --c


drop table Procedures_Versions
DECLARE @toEx VARCHAR(50)

SELECT @toEx = PV.DoProcedure
FROM Procedures_Versions PV
WHERE PV.CorrespondingVersion = 1

EXEC(@toEx)
go


CREATE PROCEDURE GetCurrentVersion(@version INT OUTPUT)
AS
	SELECT @version = CurrentVersion
	FROM CurrentVersion
GO

CREATE PROCEDURE GetDoFunction(@version INT, @doProcedure VARCHAR(50) OUTPUT)
AS 
	SELECT @doProcedure = PV.DoProcedure
	FROM Procedures_Versions PV
	WHERE PV.CorrespondingVersion = @version
GO

CREATE PROCEDURE GetUndoFunction(@version INT, @undoProcedure VARCHAR(50) OUTPUT)
AS 
	SELECT @undoProcedure = PV.UndoProcedure
	FROM Procedures_Versions PV
	WHERE PV.CorrespondingVersion = @version
GO

CREATE PROCEDURE UpdateCurrentVersion(@version INT)
AS
	UPDATE CurrentVersion
	SET CurrentVersion = @version
GO

CREATE PROCEDURE GetDatabaseToSpecifiedVersion(@desiredVersion INT)
AS
	--print @desiredVersion
	DECLARE @version int
	EXEC GetCurrentVersion @version = @version OUTPUT

	DECLARE @doProcedure VARCHAR(50)
	DECLARE @undoProcedure VARCHAR(50)

	IF @desiredVersion > @version
	BEGIN
		WHILE @desiredVersion != @version
		BEGIN
		-- 0 1 -create_table
			SET @version = @version + 1
			EXEC GetDoFunction @version, @doProcedure = @doProcedure OUTPUT
			print 'Executing ' + @doprocedure + '...'
			EXEC @doProcedure
			EXEC UpdateCurrentVersion @version
		END
	END

	ELSE

	BEGIN
		WHILE @desiredVersion != @version
		BEGIN
			EXEC GetUndoFunction @version, @undoProcedure = @undoProcedure OUTPUT
			SET @version = @version - 1
			print 'Executing ' + @undoprocedure + '...'
			EXEC @undoProcedure
			EXEC UpdateCurrentVersion @version
		END
	END
GO

drop procedure GetDatabaseToSpecifiedVersion
go

EXEC GetDatabaseToSpecifiedVersion 0
SELECT * FROM Procedures_Versions
SELECT * FROM CurrentVersion
SELECT * FROM TennisRacket