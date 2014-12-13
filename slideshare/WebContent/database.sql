-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Nov 29, 2014 at 09:25 PM
-- Server version: 5.6.21-log
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `test`
--

-- --------------------------------------------------------

--
-- Table structure for table `tblattendance`
--

CREATE TABLE IF NOT EXISTS `tblattendance` (
  `classid` varchar(100) NOT NULL,
  `studentid` varchar(100) NOT NULL,
  `date` varchar(100) NOT NULL,
  PRIMARY KEY (`classid`,`studentid`,`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tblattendance`
--

INSERT INTO `tblattendance` (`classid`, `studentid`, `date`) VALUES
('24', '201411113', '29/11/2014'),
('24', '201411113', '30/11/2014'),
('24', '201411115', '29/11/2014'),
('24', '201411115', '30/11/2014'),
('24', '201411116', '30/11/2014');

-- --------------------------------------------------------

--
-- Table structure for table `tblclass`
--

CREATE TABLE IF NOT EXISTS `tblclass` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `room` varchar(100) NOT NULL,
  `professorid` varchar(100) NOT NULL,
  `time` varchar(100) NOT NULL,
  `location` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=30 ;

--
-- Dumping data for table `tblclass`
--

INSERT INTO `tblclass` (`id`, `room`, `professorid`, `time`, `location`) VALUES
(1, 'Pal1025', '2', 'B', '38.898748,-77.036626'),
(2, 'Pal1025', '2', 'F', '38.898748,-77.036626'),
(4, 'Pal1025', '3', 'A', '38.898748,-77.036626'),
(5, 'Pal1025', '2', 'E', '38.898748,-77.036626'),
(6, 'Pal1025', '1', 'D', '38.898748,-77.036626'),
(24, 'Pall1025', '1', 'C', '38.898748,-77.036626');

-- --------------------------------------------------------

--
-- Table structure for table `tblenroll`
--

CREATE TABLE IF NOT EXISTS `tblenroll` (
  `id` int(100) NOT NULL AUTO_INCREMENT,
  `classid` varchar(100) NOT NULL,
  `studentid` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=37 ;

--
-- Dumping data for table `tblenroll`
--

INSERT INTO `tblenroll` (`id`, `classid`, `studentid`) VALUES
(19, '24', '201411113'),
(20, '24', '201411116'),
(21, '24', '201411115');

-- --------------------------------------------------------

--
-- Table structure for table `tblprofessor`
--

CREATE TABLE IF NOT EXISTS `tblprofessor` (
  `id` varchar(100) NOT NULL,
  `name` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tblprofessor`
--

INSERT INTO `tblprofessor` (`id`, `name`, `password`) VALUES
('1', 'Prof. Seok-Won Lee', 'abc'),
('2', 'Prof. Kyung-Ah Sohn', 'abc'),
('3', 'Prof. Dong Yoon Kim', 'abc'),
('4', 'abc', 'abc');

-- --------------------------------------------------------

--
-- Table structure for table `tblstudent`
--

CREATE TABLE IF NOT EXISTS `tblstudent` (
  `id` varchar(100) NOT NULL,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tblstudent`
--

INSERT INTO `tblstudent` (`id`, `name`) VALUES
('201411113', 'Vartica'),
('201411114', 'Thomas'),
('201411115', 'Sara'),
('201411116', 'Hyeon-Ju'),
('201411117', 'Hyo-cheol');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
