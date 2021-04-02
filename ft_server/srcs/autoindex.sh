#!/bin/bash

if grep -q "autoindex on" /etc/nginx/sites-available/localhost
then
	sed -i 's/autoindex on;/autoindex off;/' /etc/nginx/sites-available/localhost
	nginx -s reload
elif grep -q "autoindex off" /etc/nginx/sites-available/localhost
then
	sed -i 's/autoindex off;/autoindex on;/' /etc/nginx/sites-available/localhost
	nginx -s reload
fi

