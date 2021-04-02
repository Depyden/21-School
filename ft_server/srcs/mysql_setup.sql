CREATE DATABASE wordpress;

CREATE USER 'lregenar'@'localhost' IDENTIFIED BY 'lregenar21';
 
GRANT ALL PRIVILEGES ON wordpress.* TO 'lregenar'@'localhost';

FLUSH PRIVILEGES;
