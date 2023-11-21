-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: localhost    Database: skischool
-- ------------------------------------------------------
-- Server version	8.0.34

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `availability`
--

DROP TABLE IF EXISTS `availability`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `availability` (
  `instructor_id` int NOT NULL,
  `day` varchar(10) NOT NULL,
  `8AM` tinyint NOT NULL DEFAULT '1',
  `9AM` tinyint NOT NULL DEFAULT '1',
  `10AM` tinyint NOT NULL DEFAULT '1',
  `11AM` tinyint NOT NULL DEFAULT '1',
  `12PM` tinyint NOT NULL DEFAULT '1',
  `1PM` tinyint NOT NULL DEFAULT '1',
  `2PM` tinyint NOT NULL DEFAULT '1',
  `3PM` tinyint NOT NULL DEFAULT '1',
  PRIMARY KEY (`instructor_id`,`day`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `availability`
--

LOCK TABLES `availability` WRITE;
/*!40000 ALTER TABLE `availability` DISABLE KEYS */;
INSERT INTO `availability` VALUES (1,'Friday',1,1,1,1,1,1,1,1),(1,'Monday',1,2,1,1,1,1,1,1),(1,'Saturday',1,1,1,1,2,2,1,1),(1,'Sunday',1,1,1,1,1,1,1,1),(1,'Thursday',1,1,1,1,1,1,1,1),(1,'Tuesday',1,1,1,1,1,1,1,1),(1,'Wednesday',1,1,1,1,1,1,1,1),(2,'Friday',0,0,0,0,0,0,0,0),(2,'Monday',0,0,0,0,0,0,0,0),(2,'Saturday',0,0,0,0,0,0,0,0),(2,'Sunday',0,0,0,0,0,0,0,0),(2,'Thursday',0,0,0,0,0,0,0,0),(2,'Tuesday',0,0,0,0,0,0,0,0),(2,'Wednesday',0,0,0,0,0,0,0,0),(3,'Friday',1,1,1,1,1,1,1,1),(3,'Monday',1,1,1,1,1,1,1,1),(3,'Saturday',1,1,1,1,1,1,1,1),(3,'Sunday',1,1,1,1,1,1,1,1),(3,'Thursday',1,1,1,1,1,1,1,1),(3,'Tuesday',1,1,1,1,1,1,1,1),(3,'Wednesday',1,1,1,1,1,1,1,1),(4,'Friday',1,1,1,1,1,1,1,1),(4,'Monday',0,0,1,1,1,1,1,1),(4,'Saturday',1,1,1,1,1,1,1,1),(4,'Sunday',1,1,1,1,1,1,1,1),(4,'Thursday',1,1,2,2,1,1,1,1),(4,'Tuesday',1,1,1,1,1,1,1,1),(4,'Wednesday',0,0,0,0,0,0,0,0),(5,'Friday',1,1,1,1,1,1,1,1),(5,'Monday',1,1,1,1,1,1,1,1),(5,'Saturday',1,1,1,1,1,1,1,1),(5,'Sunday',1,1,1,1,1,1,1,1),(5,'Thursday',1,1,1,1,1,1,1,1),(5,'Tuesday',1,1,1,1,1,1,1,1),(5,'Wednesday',1,1,1,1,1,1,1,1),(6,'Friday',1,1,1,1,1,1,1,1),(6,'Monday',1,1,1,1,1,1,1,1),(6,'Saturday',1,1,1,1,1,1,1,1),(6,'Sunday',1,1,1,1,1,1,1,1),(6,'Thursday',1,1,1,1,1,1,1,1),(6,'Tuesday',1,1,1,1,1,1,1,1),(6,'Wednesday',1,1,1,1,1,1,1,1);
/*!40000 ALTER TABLE `availability` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-21 23:59:28
