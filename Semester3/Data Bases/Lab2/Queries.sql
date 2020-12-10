USE ATPDB
GO

--a. 2 queries with the union operation; use UNION [ALL] and OR;
-- get all players from Russia and Spain who have at least 4000 points or who won at least a grandslam

SELECT * FROM Player
SELECT * FROM Tournament
SELECT * FROM TournamentWinner
SELECT * FROM Umpire
SELECT * FROM Coach

SELECT P2.FirstName, P2.LastName 
FROM Player P2
WHERE (P2.OriginCountry = 'Russia' or P2.OriginCountry = 'Spain') AND P2.PlayerId IN (
	SELECT P.PlayerId
	FROM Player P
	WHERE  P.NumberOfPoints > 3000

	UNION ALL

	SELECT TW.PlayerId
	FROM TournamentWinner TW
	WHERE TW.TournamentId IN(
		SELECT TournamentId
		FROM Tournament
		WHERE TTYPE = 'Grand Slam'
	)
)

-- get all players youner than 24 (BORN BEFORE 1996) or are from Russia

SELECT CONVERT (DATE, SYSDATETIME()) 

SELECT * FROM Player

SELECT P.FirstName, P.LastName
FROM Player P
WHERE P.DateOfBirth < '1996-01-01' OR P.OriginCountry = 'Russia'

SELECT TOP 10 Player.FirstName, Player.LastName, Player.NumberOfPoints
FROM Player
ORDER BY Player.NumberOfPoints DESC

--b. 2 queries with the intersection operation; use INTERSECT and IN;
-- get all players that are younger than 23 (born before 2000) and have Adidas as a sponsor

SELECT P2.FirstName, P2.LastName 
FROM Player P2
WHERE P2.PlayerId IN (
	SELECT P.PlayerId
	FROM Player P
	WHERE P.DateOfBirth > '1997-01-01' 

	INTERSECT

	SELECT PS.PlayerId
	FROM Player_Sponsor PS
	WHERE PS.SponsorId = (
		SELECT S.SponsorId
		FROM Sponsor S
		WHERE S.SponsorName = 'Adidas'
	)

)

SELECT * FROM Umpire
SELECT * FROM Match_Umpire
SELECT * FROM TennisMatch

-- get all chair umpires who have a sallary > 500 and were the umpires of at least 2 matches
SELECT U.UmpireName
FROM Umpire U
WHERE U.UmpireId IN(
	SELECT U2.UmpireId
	FROM Umpire U2
	WHERE U2.UType = 'Chair' and  U2.MonthlyIncome > 500

	INTERSECT

	SELECT MU.UmpireId
	FROM Match_Umpire MU
	GROUP BY MU.UmpireId
	HAVING 2 <= (
		SELECT COUNT(*)
		FROM Match_Umpire MU2
		WHERE MU.UmpireId = MU2.UmpireId
	)

)

--c. 2 queries with the difference operation; use EXCEPT and NOT IN;
-- select the players who have more than 5000 points but did not win a grand slam

SELECT TOP 3 P.FirstName, P.LastName
FROM Player P
WHERE P.PlayerId IN (
	SELECT P2.PlayerId
	FROM Player P2
	WHERE P2.NumberOfPoints > 5000

	EXCEPT

	SELECT TW.PlayerId
	FROM TournamentWinner TW
	WHERE TW. TournamentId IN (
		SELECT TournamentId
		FROM Tournament
		WHERE TTYPE = 'Grand Slam'
	)
)

-- find the players who didn't win any tournament

SELECT * FROM TournamentWinner

SELECT P.FirstName, P.LastName
FROM Player P
WHERE P.PlayerId NOT IN (
	SELECT TW.PlayerId
	FROM TournamentWinner TW
)
ORDER BY P.LastName

--d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator);
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

SELECT P.PlayerId, P.FirstName, P.LastName, P.NumberOfPoints, T.TournamentName, T.TType AS "Tournamet Type"
FROM Player P INNER JOIN Player_Tournamnet PT ON P.PlayerId = PT.PlayerId INNER JOIN Tournament T ON T.TournamentId = PT.TournamentId
ORDER BY P.NumberOfPoints DESC

SELECT *
FROM Umpire U LEFT JOIN Match_Umpire MU ON U.UmpireId = MU.UmpireId

SELECT *
FROM Coach C RIGHT JOIN Player P ON C.PlayerId = P.PlayerId 

SELECT *
FROM Tournament T FULL JOIN Player_Tournamnet PT ON T.TournamentId = PT.TournamentId FULL JOIN Player P ON PT.PlayerId = P.PlayerId FULL JOIN Player_Sponsor PS ON P.PlayerId = PS.PlayerId

--e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause;

--SHOW ALL THE PLAYERS WHO HAVE WON AT LEAST A TOURNAMENT
SELECT Player.FirstName, Player.LastName
FROM Player 
WHERE PlayerId IN(
	SELECT PlayerId
	FROM TournamentWinner
)
--SHOW ALL THE PLAYERS WHO HAVE WON AT LEAST A GRAND SLAM
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

-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

--SELECT ALL PLAYERS WHO HAVE AT LEAST A SPONSOR
SELECT P.FirstName, P.LastName
FROM Player P
WHERE EXISTS (
	SELECT *
	FROM Player_Sponsor
	WHERE P.PlayerId = Player_Sponsor.PlayerId
)

-- SELECT ALL PLAYERS WHO PARTICIPATED IN AT LEAST A TOURNAMENT
SELECT P.FirstName, P.LastName
FROM Player P
WHERE EXISTS (
	SELECT *
	FROM Player_Tournamnet
	WHERE P.PlayerId = Player_Tournamnet.PlayerId
)

--g. 2 queries with a subquery in the FROM clause;      

-- select from the players that won at least a tournament, the ones that have more than 5000 points
SELECT DISTINCT P2.FirstName, P2.LastName
FROM (
	SELECT *
	FROM Player P
	WHERE PlayerId IN(
		SELECT PlayerId
		FROM TournamentWinner
	)
) AS P2
WHERE P2.NumberOfPoints > 5000

SELECT * FROM Player

-- select from all the players who participated at us open, the ones who have nike as their sponsor
SELECT P2.FirstName, P2.LastName
FROM (
	SELECT P.PlayerId, P.FirstName, P.LastName
	FROM Player P INNER JOIN Player_Tournamnet PT ON P.PlayerId = PT.PlayerId
	WHERE PT.TournamentId = 3

) AS P2
WHERE P2.PlayerId IN (
	SELECT PS.PlayerId
	FROM Sponsor S INNER JOIN Player_Sponsor PS ON S.SponsorId = PS.SponsorId 
	WHERE PS.SponsorId = 1
)

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; 
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- find the player with most points for each country

SELECT * FROM Tournament
SELECT * FROM Player
SELECT * FROM TournamentWinner

SELECT  MAX(P.NumberOfPoints) AS "MAX POINTS", P.OriginCountry
FROM Player P
GROUP BY P.OriginCountry

-- find the average of the monthly income of umpires grouped by type, where average greater than the average income of a coach
SELECT U.UType, AVG(U.MonthlyIncome) AS "Average Salary"
FROM Umpire U
GROUP BY U.UType
HAVING  AVG(U.MonthlyIncome) > (
	SELECT AVG(C.MonthlyIncome) 
	FROM Coach C
)

-- calculate the sum of prizes for each type of tournament that has at least 2 tournaments of such type
SELECT T.TType, SUM(T.Prize) AS "Sum of prizes"
FROM Tournament T
GROUP BY T.TType
HAVING 2 <= (
	SELECT COUNT(*)
	FROM Tournament T2
	WHERE T.TType = T2.TType
)

-- finds the mimum prize of a tournament greater than 250000
SELECT T.NrOfPoints, MIN(T.Prize) AS "Minimum prize"
FROM Tournament T
GROUP BY T.NrOfPoints
HAVING MIN(T.Prize) > 250000

--i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.


-- find the name and prize for the tournamet with the most points
SELECT T.TournamentName, T.NrOfPoints
FROM Tournament T
WHERE  T.NrOfPoints = ANY (
		SELECT MAX(T2.NrOfPoints)
		FROM Tournament T2
	)

SELECT T.TournamentName, MAX(T.NrOfPoints) AS NrOfPoints
FROM Tournament T
GROUP BY T.TournamentName
HAVING MAX(T.NrOfPoints) = (
	SELECT MAX(T2.NrOfPoints)
	FROM Tournament T2
)

-- find the name of the coach with the biggest sallary

SELECT * FROM Coach

SELECT C.CoachName, C.MonthlyIncome
FROM Coach C
WHERE C.MonthlyIncome >=  ALL(
	SELECT AVG(C2.MonthlyIncome)
	FROM Coach C2
)ORDER BY C.CoachName

SELECT C.CoachName, AVG(C.MonthlyIncome) AS 'Average Monthly income'
FROM Coach C
GROUP BY C.CoachName
HAVING AVG(C.MonthlyIncome) >= (
	SELECT AVG(C2.MonthlyIncome)
	FROM Coach C2
)ORDER BY C.CoachName

--players who won at least a grand slam
SELECT TW.PlayerId
	FROM TournamentWinner TW
	WHERE TW.TournamentId = ANY(
		SELECT TournamentId
		FROM Tournament
		WHERE TTYPE = 'Grand Slam'
	)

SELECT TW.PlayerId
	FROM TournamentWinner TW
	WHERE TW.TournamentId IN( 
		SELECT TournamentId
		FROM Tournament
		WHERE TTYPE = 'Grand Slam'
	)


-- find the players who didn't win any tournament
SELECT DISTINCT P.FirstName, P.LastName
FROM Player P
WHERE P.PlayerId != ALL (
	SELECT TW.PlayerId
	FROM TournamentWinner TW
)

SELECT DISTINCT P.FirstName, P.LastName
FROM Player P
WHERE P.PlayerId NOT IN (
	SELECT TW.PlayerId
	FROM TournamentWinner TW
)
