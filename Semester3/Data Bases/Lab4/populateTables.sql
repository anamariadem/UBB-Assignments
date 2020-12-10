
SELECT * FROM Player
go

SELECT * FROM Tournament
GO

CREATE VIEW RandomView
AS
SELECT RAND() AS RandomValue
GO


--DROP FUNCTION function_random_int
GO
CREATE FUNCTION generate_random_int(
	@leftBound INT,
	@rightBound INT
)
RETURNS INT
AS
BEGIN
	RETURN FLOOR((SELECT RandomValue FROM RandomView) * (@rightBound - @leftBound) + @leftBound)
END
GO

CREATE PROCEDURE insertPlayer @identity INT
AS
BEGIN 
	INSERT INTO Player(PlayerId, FirstName, LastName, DateOfBirth, NumberOfPoints, OriginCountry) VALUES
	(@identity, 
	'FirstName' + CONVERT(VARCHAR(10), @identity),
	'LastName' + CONVERT(VARCHAR(10), @identity),
	'1990-04-07',
	dbo.generate_random_int(1000, 7000),
	'Country' + CONVERT(VARCHAR(10), @identity)
	)
END
GO

CREATE PROCEDURE insertTournament @identity INT
AS
BEGIN
	INSERT INTO Tournament(TournamentId, TournamentName, StartDate, TType, NrOfPoints, Prize) VALUES
	(@identity,
	'Name:'+ CONVERT(VARCHAR(10), @identity),
	'2020-11-23',
	'Type:'+ CONVERT(VARCHAR(10), @identity),
	dbo.generate_random_int(100, 1500),
	dbo.generate_random_int(10000, 1000000)
	)
END
GO

CREATE PROCEDURE insertCoach @identity INT
AS
BEGIN
	INSERT INTO Coach(CoachId, CoachName, PlayerId, MonthlyIncome) VALUES
	(@identity,
	'Coach' + CONVERT(VARCHAR(10), @identity),
	(SELECT TOP 1 PlayerId FROM Player ORDER BY NEWID()),
	dbo.generate_random_int(100, 1500))
END
GO

CREATE PROCEDURE insertSponsor @identity INT
AS
BEGIN
	INSERT INTO Sponsor(SponsorId, SponsorName) VALUES
	(@identity,
	'SponsorName' + CONVERT(VARCHAR(10), @identity))
END
GO

CREATE PROCEDURE insertPlayer_Sponsor @identity INT
AS
BEGIN
	DECLARE @playerId INT, @sponsorId INT, @inserted BIT
	SET @inserted = 0

	WHILE @inserted = 0
	BEGIN
		SET @playerId = (SELECT TOP 1 PlayerId from Player ORDER BY NEWID())
		SET @sponsorId = (SELECT TOP 1 SponsorId from Sponsor ORDER BY NEWID())

		--define a new table that holds all the rows from Player_Sponsor with PlayerId = @playerId
		--check if there is a row in the new tanle with SponsorId = @sponsorId

		IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Player_Sponsor_FixedPlayerId' )
		BEGIN
			DROP TABLE Player_Sponsor_FixedPlayerId
		END

		SELECT * INTO Player_Sponsor_FixedPlayerId
		FROM Player_Sponsor
		WHERE PlayerId = @playerId

		IF NOT EXISTS (SELECT * FROM Player_Sponsor_FixedPlayerId WHERE SponsorId = @sponsorId)
		BEGIN
			INSERT INTO Player_Sponsor(PlayerId,SponsorId) VALUES
			(@playerId, @sponsorId)

			SET @inserted = 1
		END
	END

END
GO

CREATE PROCEDURE populateTable @table VARCHAR(50), @numberOfRows INT
AS
BEGIN
	 DECLARE @currentRow INT, @procedure VARCHAR(100)
	 SET @currentRow = 0

	 WHILE @currentRow < @numberOfRows
	 BEGIN
		SET @procedure = 'insert' + @table + ' ' + CONVERT (VARCHAR(5), @currentRow)
		EXEC (@procedure)
		--print 'executing' + @procedure + '....'
		SET @currentRow = @currentRow + 1
	 END
END
GO

drop procedure populateTable

delete from TennisRacket
delete from Player
EXEC populateTable 'Player', 2000
EXEC populateTable 'Sponsor', 10
EXEC populateTable 'Player_Sponsor', 5
EXEC populateTable 'Coach', 7

SELECT * from Player
SELECT * from Sponsor
SELECT * from Player_Sponsor
SELECT * from Coach



select * from PlayersCopy
select * from SponsorsCopy 
select * from CoachesCopy 
select * from Players_SponsorsCopy 

delete from Coach
delete from Player_Sponsor
delete from Sponsor
delete from Player_Tournamnet
delete from TournamentWinner
delete from Player