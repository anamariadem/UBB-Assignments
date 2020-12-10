--DROP TABLE Player


CREATE TABLE Player
(PlayerId INT PRIMARY KEY,
FirstName VARCHAR(50),
LastName VARCHAR(50),
DateOfBirth DATE,
RankId INT REFERENCES Ranking(RankId)
)

CREATE TABLE Tournament
(TournamentId INT PRIMARY KEY,
TournamentName VARCHAR(50),
StartDate DATE)

CREATE TABLE Coach
( CoachId INT PRIMARY KEY,
CoachName VARCHAR(50),
PlayerId INT REFERENCES Player(PlayerId)
)


CREATE TABLE Sponsor
( SponsorId INT PRIMARY KEY,
SponsorName VARCHAR(50))

CREATE TABLE TennisMatch
(MatchId INT PRIMARY KEY,
MatchScore VARCHAR(50),
TournamentId INT REFERENCES Tournament(TournamentId)
)

CREATE TABLE Umpire
( UmpireId INT PRIMARY KEY, 
UmpireName VARCHAR(50),
MatchId INT REFERENCES TennisMatch(MatchID)
)

CREATE TABLE TournamentWinner
(PlayerId INT PRIMARY KEY REFERENCES Player(PlayerId), 
Section VARCHAR(50),
TournamentId INT REFERENCES Tournament(TournamentId)
)

DROP TABLE TournamentWinner

CREATE TABLE Player_Tournamnet
(PlayerId INT REFERENCES Player(PlayerId),
TournamentId INT REFERENCES Tournament(TournamentId),
PRIMARY KEY(PlayerId, TournamentId))

CREATE TABLE Player_Sponsor
(PlayerId INT REFERENCES Player(PlayerId),
SponsorId INT REFERENCES Sponsor(SponsorId),
PRIMARY KEY(PlayerId, SponsorId))


CREATE TABLE Player_Match
(PlayerId INT REFERENCES Player(PlayerId),
MatchId INT REFERENCES TennisMatch(MatchId),
PRIMARY KEY(PlayerId, MatchId))


 ALTER TABLE Player
 ADD OriginCountry VARCHAR(50);