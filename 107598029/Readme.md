# �p��ϥ�

* IDE�GIntlliJ IDEA 2018.3.5 x64
* Tomcat�G`Tomcat9.0.12`
* DataBase�GMySQL

* IntelliJ > File > open > {homework path} > 107598029/HW1
* Defult URL�GEdit Conigurations > URL > http://localhost:8080/list

# �`�N�ƶ�

�������� MySQL �إ� �W���Gsa ����Ʈw
���ۦb��Ʈw�U�إߦ�����

* DataBase Schema
```
CREATE TABLE `coursesys` (
  `courseid` int(11) NOT NULL AUTO_INCREMENT,
  `coursename` varchar(45) NOT NULL,
  `courselevel` varchar(45) DEFAULT NULL,
  `courseprice` int(11) DEFAULT NULL,
  `coursedescription` varchar(45) DEFAULT NULL,
  `precautions` varchar(45) DEFAULT NULL,
  `remarks` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`courseid`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

```