USE ATPDB
GO
ALTER TABLE Tournament
	ADD CONSTRAINT UniqPrize UNIQUE (Prize)

SELECT * FROM Tournament
select * from Player
INSERT INTO Tournament(TournamentId, TournamentName, StartDate, TType, NrOfPoints, Prize) VALUES
	(1, 'Australian Open', '2021-01-07', 'grand slam', 2000, 123000),
	(2, 'US Open', '2021-09-07', 'grand slam', 2000, 235000),
	(3, 'Wimbledon', '2021-07-07', 'grand slam', 2000, 256450),
	(4, 'Roland Garros', '2021-06-10', 'grand slam', 2000, 453050),
	(5, 'Paris Open', '2021-11-07', 'masters', 1000, 23000),
	(6, 'Rome Open', '2021-05-14', 'masters', 1000, 60000),
	(7, 'ATP Finals', '2021-11-23', 'grand slam', 1500, 223000),
	(8, 'Sofia Open', '2021-10-05', 'atp 500', 500, 11000),
	(9, 'BNP Paribas Open', '2021-01-07', 'masters', 1000, 34000),
	(10, 'Vienna Open', '2021-01-07', 'atp 500', 500, 19000),
	(11, 'Madrid Open', '2021-05-07', 'masters', 1000, 55000)

--ta tournament
--tb player

CREATE TABLE TennisRacket 
( RacketId INT PRIMARY KEY,
  TournamentId INT REFERENCES Tournament(TournamentId),
  PlayerId INT REFERENCES Player(PlayerId),
  Brand VARCHAR(50),
  Model VARCHAR(50),
  TimePlayed INT
)

INSERT INTO TennisRacket(RacketId, TournamentId, PlayerId, Brand, Model, TimePlayed) VALUES
	(1, 1, 1, 'Head', 'GForceX', 45),
	(2, 10, 3, 'Babolar', 'BWR Power', 33),
	(3, 11, 7, 'Head', 'GForceX', 35),
	(4, 4, 2, 'Babolar', 'RN', 25),
	(5, 3, 4, 'Wilson', 'peRfect power', 29),
	(6, 9, 6, 'Head', 'GForceX', 45),
	(7, 8, 8, 'Babolar', 'X', 45),
	(8, 2, 12, 'Wilson', 'Power+', 44),
	(9, 1, 13, 'Wilson', 'Power+', 45),
	(10, 5, 5 ,'Head', 'GForceX', 45)
go
--a
sp_helpindex Player
go

sp_helpindex TennisRacket
--clustered index seek
select *
from tennisracket
where racketid = 3

--clustered index scan
select * 
from tennisracket
where Model = 'model'

DROP INDEX IF EXISTS index_tournament ON Tournament
CREATE NONCLUSTERED INDEX index_tournament ON Tournament(Prize)
sp_helpindex Tournament

--nonclustered index scan
SELECT * 
FROM Tournament
ORDER BY Prize

--nonclustered index seek
SELECT *
FROM Tournament
WHERE Prize > 20000

--lookup
SELECT Prize, TournamentName
FROM Tournament
ORDER BY Prize

--b
--subtree cost 0.0032985 - no index
SELECT *
FROM Player
WHERE NumberOfPoints = 9850

CREATE NONCLUSTERED INDEX index_player ON Player(NumberOfPoints)
DROP INDEX IF EXISTS index_player ON Player
--the nonclustered index is used for 2000 elements
--the nonclustered index is not used for 15 elements
SELECT *
FROM Player
WHERE NumberOfPoints = 9850
go

--c
CREATE OR ALTER VIEW player_racket
AS
	SELECT P.PlayerId, P.FirstName, P.LastName, P.NumberOfPoints, T.TournamentId, TR.Brand, TR.Model, TR.TimePlayed, T.Prize, T.NrOfPoints
	FROM Player P INNER JOIN TennisRacket TR ON P.PlayerId = TR.PlayerId INNER JOIN Tournament T ON TR.TournamentId = T.TournamentId
	WHERE P.NumberOfPoints > 2000 AND T.NrOfPoints > 1000 AND TR.TimePlayed >20
GO

--subtree cost 0.0098599
SELECT * 
FROM player_racket

select * from Player

CREATE NONCLUSTERED INDEX index_tournament_points ON Tournament(NrOfPoints)
CREATE NONCLUSTERED INDEX index_racket_time_played ON TennisRacket(TimePlayed)
sp_helpindex Tournament
go
sp_helpindex Player
go

sp_helpindex TennisRacket
--index is not used for Tournament
--table is too small, the index is not used for TennisRacket
--the system uses the clustered indexes

DROP INDEX IF EXISTS index_tournament_points ON Tournament