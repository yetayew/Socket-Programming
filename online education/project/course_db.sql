-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 30, 2022 at 05:35 PM
-- Server version: 10.4.24-MariaDB
-- PHP Version: 8.1.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `course_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `bookmark`
--

CREATE TABLE `bookmark` (
  `user_id` varchar(20) NOT NULL,
  `playlist_id` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `comments`
--

CREATE TABLE `comments` (
  `id` varchar(20) NOT NULL,
  `content_id` varchar(20) NOT NULL,
  `user_id` varchar(20) NOT NULL,
  `tutor_id` varchar(20) NOT NULL,
  `comment` varchar(1000) NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `contact`
--

CREATE TABLE `contact` (
  `name` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `number` int(10) NOT NULL,
  `message` varchar(1000) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `content`
--

CREATE TABLE `content` (
  `id` varchar(20) NOT NULL,
  `tutor_id` varchar(20) NOT NULL,
  `playlist_id` varchar(20) NOT NULL,
  `title` varchar(100) NOT NULL,
  `description` varchar(1000) NOT NULL,
  `video` varchar(100) NOT NULL,
  `thumb` varchar(100) NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp(),
  `status` varchar(20) NOT NULL DEFAULT 'deactive'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `likes`
--

CREATE TABLE `likes` (
  `user_id` varchar(20) NOT NULL,
  `tutor_id` varchar(20) NOT NULL,
  `content_id` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `playlist`
--

CREATE TABLE `playlist` (
  `id` varchar(20) NOT NULL,
  `tutor_id` varchar(20) NOT NULL,
  `title` varchar(100) NOT NULL,
  `description` varchar(1000) NOT NULL,
  `thumb` varchar(100) NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp(),
  `status` varchar(20) NOT NULL DEFAULT 'deactive'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `tutors`
--

CREATE TABLE `tutors` (
  `id` varchar(20) NOT NULL,
  `name` varchar(50) NOT NULL,
  `profession` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `image` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` varchar(20) NOT NULL,
  `name` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `image` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
CREATE TABLE Address (
    Email VARCHAR(30),
    Country VARCHAR(30),
    State VARCHAR(30),
    City VARCHAR(30),
    Street VARCHAR(50),
    PRIMARY KEY (Email)
);
CREATE TABLE Std_Phone (
    Phone_Number VARCHAR(15),
    std_id INT,
    PRIMARY KEY (Phone_Number , std_id),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID)
);
CREATE TABLE Ins_Phone (
    Phone_Number VARCHAR(15),
    ins_id INT,
    PRIMARY KEY (Phone_Number , ins_id),
    FOREIGN KEY (ins_id)
        REFERENCES Instructor (ins_ID)
);
CREATE TABLE FeedBack (
    FdBk_ID INT,
    comments VARCHAR(150),
    Date_and_Time DATETIME,
    PRIMARY KEY (FdBk_ID)
);

-- student's Feedback
CREATE TABLE Fdbk (
    std_id INT,
    fdbk_id INT,
    PRIMARY KEY (std_id , fdbk_id),
    FOREIGN KEY (fdbk_id)
        REFERENCES FeedBack (FdBk_ID),
    FOREIGN KEY (std_id)
        REFERENCES student (std_ID)
);
CREATE TABLE Instructor (
    ins_ID INT,
    First_Name VARCHAR(20) NOT NULL,
    Last_Name VARCHAR(20) NOT NULL,
    dept_name varchar(30),
    Gender VARCHAR(1),
    Education_Level VARCHAR(15) NOT NULL,
    salary DECIMAL(7 , 2 ),
    ins_email VARCHAR(15),
    PRIMARY KEY (ins_ID),
    FOREIGN KEY (ins_email)
        REFERENCES Address (Email),
    FOREIGN KEY (dept_name)
        REFERENCES Department (Department_Name),
    CHECK (Gender = 'M' OR 'F')
);

-- teaches table that relates instructor with course
CREATE TABLE Teaches (
    ins_ID INT,
    course_ID VARCHAR(10),
    PRIMARY KEY (ins_ID , course_ID),
    FOREIGN KEY (course_ID)
        REFERENCES Courses (course_ID),
    FOREIGN KEY (ins_ID)
        REFERENCES instructor (ins_ID)
);
CREATE TABLE Courses (
    course_ID VARCHAR(10),
    Credit_Hour INT DEFAULT 0,
    price DECIMAL(6 , 2 ) DEFAULT 0,
    Title VARCHAR(20) NOT NULL,
    mat_id VARCHAR(10),
    PRIMARY KEY (course_ID),
    FOREIGN KEY (mat_id)
        REFERENCES Material (Mat_ID)
);

-- table "takes" relate student with the course he/she takes
CREATE TABLE Takes (
    std_id INT,
    course_id VARCHAR(10),
    Grade VARCHAR(1),
    PRIMARY KEY (std_id , course_id),
    FOREIGN KEY (course_id)
        REFERENCES Courses (course_ID),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID)
);
CREATE TABLE Department (
    Department_Name VARCHAR(20),
    Dean VARCHAR(20) NOT NULL,
    No_of_Instructor INT,
    No_of_Courses INT NOT NULL,
    No_of_Students INT,
    PRIMARY KEY (Department_Name)
);

-- courses in a department
CREATE TABLE Dept_Course(
    course_id VARCHAR(10),
    dept_name VARCHAR(20),
    PRIMARY KEY (course_id , dept_name),
    FOREIGN KEY (course_id)
        REFERENCES Courses (course_ID),
    FOREIGN KEY (dept_name)
        REFERENCES Department(Department_Name)
);
CREATE TABLE Accounts (
    Register_ID INT,
    std_id INT,
    ins_id INT,
    Registration_Dtae DATE,
    Status_of_Account VARCHAR(10) DEFAULT 'unknown',
    Type_of_Account VARCHAR(10) DEFAULT 'unknown',
    PRIMARY KEY (Register_ID),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID),
    FOREIGN KEY (ins_id)
        REFERENCES Instructor (ins_ID)
);
CREATE TABLE Payment (
    Payment_ID INT,
    Method VARCHAR(30) DEFAULT 'CBE',
    Status_of_Payment VARCHAR(10) DEFAULT 'not paid',
    Amount DECIMAL(7 , 2 ) DEFAULT 0,
    PRIMARY KEY (Payment_ID)
);

-- table "pay" is whether the students pay his/her payment
CREATE TABLE Pay (
    std_id INT,
    payment_id INT,
    PRIMARY KEY (std_id , payment_id),
    FOREIGN KEY (payment_id)
        REFERENCES Payment (Payment_ID),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID)
);

CREATE TABLE Section (
    section_ID INT,
    No_of_Student INT,
    semester VARCHAR(2),
    year YEAR,
    PRIMARY KEY (section_ID , semester , year)
);

-- cources given in a section
CREATE TABLE Sec_Course (
    sec_id INT,
    course_id VARCHAR(10),
    semester VARCHAR(2),
    year YEAR,
    PRIMARY KEY (sec_id , course_id , semester , year),
    FOREIGN KEY (course_id)
        REFERENCES Courses (course_ID),
    FOREIGN KEY (sec_id , semester , year)
        REFERENCES Section (section_ID , semester , year)
);

-- student in which section
CREATE TABLE Is_Sec (
    sec_id INT,
    std_id int,
    semester VARCHAR(2),
    year YEAR,
    PRIMARY KEY (sec_id , std_id , semester , year),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID),
    FOREIGN KEY (sec_id , semester , year)
        REFERENCES Section (section_ID , semester , year)
);


CREATE TABLE Material (
    Mat_ID VARCHAR(10),
    Title VARCHAR(30),
    URL VARCHAR(100),
    type_of_Material VARCHAR(10),
    PRIMARY KEY (Mat_ID)
);
CREATE TABLE Exams (
    Assignment INT,
    Quize INT,
    Mid_Exam INT,
    Final_Exame INT,
    std_id INT,
    course_id VARCHAR(10),
    PRIMARY KEY (std_id , course_id),
    FOREIGN KEY (std_id)
        REFERENCES Student (std_ID),
    FOREIGN KEY (course_id)
        REFERENCES Courses (course_ID)
);
CREATE TABLE Schedules (
    schedule_ID INT,
    Date_and_Time DATETIME,
    PRIMARY KEY (schedule_ID)
);

-- schedule we have in a section
CREATE TABLE Sec_Sched (
    sch_id int,
    sec_id INT,
    semester VARCHAR(2),
    year YEAR,
    PRIMARY KEY ( sch_id , sec_id ,semester , year),
    FOREIGN KEY (sch_id)
        REFERENCES Schedules (schedule_ID),
    FOREIGN KEY (sec_id , semester , year)
        REFERENCES Section (section_ID , semester , year)
);
CREATE TABLE prerequisite (
    pre_req_ID VARCHAR(10),
    Course_ID VARCHAR(10),
    PRIMARY KEY (pre_req_ID , Course_ID),
    FOREIGN KEY (Course_ID)
        REFERENCES courses (Course_ID),
    FOREIGN KEY (pre_req_ID)
        REFERENCES courses (Course_ID)
);
