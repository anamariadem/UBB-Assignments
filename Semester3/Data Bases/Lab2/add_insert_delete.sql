
--inserts in tables
delete from Player
delete from Player_Sponsor
delete from Coach
INSERT Player(PlayerId, FirstName, LastName, DateOfBirth, NumberOfPoints, OriginCountry) VALUES
	(1, 'Novak', 'Djokovic', '1987-05-22', 11740, 'Serbia'),
	(2, 'Rafael', 'Nadal', '1986-06-03', 9850, 'Spain'),
	(3, 'Dominic', 'Thiem', '1993-09-03', 9125, 'Austria'),
	(4, 'Roger', 'Federer', '1981-08-08', 6630, 'Switzerland'),
	(5, 'Stefanos', 'Tsisipas', '1998-08-12', 5925, 'Greece'),
	(6, 'Daniil', 'Medvedev', '1996-02-11', 5890, 'Russia'),
	(7, 'Alexander', 'Zverev', '1997-04-20', 4650, 'Germany'),
	(8, 'Diego', 'Schwartzman', '1992-08-16', 3180, 'Argentina')

INSERT Player(PlayerId, FirstName, LastName, DateOfBirth, NumberOfPoints, OriginCountry) VALUES
	(9, 'Matteo', 'Berrettini', '1996-04-12', 3075, 'Italy'),
	(10, 'Andrey', 'Rublev', '1997-10-20', 3429, 'Russia')

INSERT Player(PlayerId, FirstName, LastName, DateOfBirth, NumberOfPoints, OriginCountry) VALUES
	(11, 'Gael', 'Monfils', '1986-09-01', 2860, 'France'),
	(12, 'Roberto', 'Bautista-Agut', '1988-04-14', 2710, 'Spain'),
	(13, 'Fabio', 'Fognini', '1987-05-24', 2400, 'Italy'),
	(14, 'Denis', 'Shapovalov', '1999-04-15', 2830, 'Canada'),
	(15, 'Milos', 'Raonic', '1990-12-27', 2265, 'Canada')

INSERT Player_Tournamnet(PlayerId, TournamentId) VALUES
	(1,6),
	(2,6),
	(3,6)

INSERT Player_Tournamnet(PlayerId, TournamentId) VALUES
	(9, 1),
	(7, 1),
	(5, 1),
	(8 ,2),
	(1, 3),
	(2, 3),
	(3, 3),
	(4, 3),
	(5, 3),
	(6, 3),
	(7, 3),
	(8, 3),
	(9, 3),
	(10, 3)

INSERT TournamentWinner (PlayerId, Section, TournamentId) VALUES 
	(6, 'Singles', 3),
	(9, 'Singles', 1),
	(8, 'Singles', 2)

--insert that violates referential integrity constraints
INSERT TournamentWinner (PlayerId, Section, TournamentId) VALUES 
	(100, 'Singles', 2)


SELECT * FROM Player
SELECT * FROM Tournament

INSERT Tournament(TournamentId, TournamentName, StartDate, TType, NrOfPoints, Prize) VALUES
	(7, 'Vienna Open', '2020-10-26', 'ATP500',500, 500000),
	(8, 'Paris', '2020-11-02', 'Masters',100, 1000000),
	(9, 'Sofia Open', '2020-11-08', 'ATP250',250, 150000),
	(10, 'ATP Finals', '2020-11-10', 'Finals', 1000, 1250000)

UPDATE Tournament
SET TTYPE = 'Grand Slam'
WHERE TournamentId = 3 or TournamentId = 6

UPDATE Tournament
SET TTYPE = 'Masters'
WHERE TournamentId IN (1, 2,4,5)

UPDATE Tournament
SET NrOfPoints = 2000
WHERE TType = 'Grand Slam'

UPDATE Tournament
SET NrOfPoints = 1000
WHERE TType = 'Masters'

UPDATE Tournament
SET Prize = 1250000
WHERE TType = 'Grand Slam'

UPDATE Tournament
SET Prize = 900000
WHERE TType = 'Masters'

ALTER TABLE Tournament
ADD TType VARCHAR(50)

ALTER TABLE Coach
ADD MonthlyIncome Int

ALTER TABLE Tournament
ADD NrOfPoints Int

ALTER TABLE Tournament
ADD Prize int

--updates

-- we have some new umpires, so we set a starting salary
UPDATE Umpire 
SET MonthlyIncome = 400
WHERE MonthlyIncome IS NULL

-- UPDATE THE NUMBER OF POINTS AFTER A PLAYER WON A TOURNAMENT
UPDATE Player
SET NumberOfPoints = NumberOfPoints + 2000
WHERE PlayerId IN (
	SELECT PlayerId
	FROM TournamentWinner
	WHERE TournamentId = 6
)

--THEY WERE THE CHAIR UMPIRES IN A GRAND SLAM FINAL SO THEY GET A RAISE
UPDATE Umpire
SET MonthlyIncome = MonthlyIncome + 3000
WHERE UmpireId = 1 OR UmpireId = 5

--UMPIRES GET A RAISE 
UPDATE Umpire
SET UType = 'Chair'
WHERE MonthlyIncome BETWEEN 5000 AND 6000

--deletes
SELECT * INTO TournamentsCopy
FROM Tournament

SELECT* FROM PlayersCopy

DELETE 
FROM TournamentsCopy 
WHERE TType LIKE 'M%'

SELECT * INTO PlayersCopy
FROM Player

DELETE 
FROM PlayersCopy
WHERE NumberOfPoints < 2500
