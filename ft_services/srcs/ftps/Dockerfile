FROM alpine

RUN apk update
RUN apk add openrc
RUN apk add vsftpd
RUN apk add openssl

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -subj '/C=RU/ST=Russia/L=Moscow/O=School21/CN=Lregenar' -keyout /etc/ssl/private/vsftpd.key -out /etc/ssl/certs/vsftpd.crt

RUN adduser -D -h /var/ftp lregenar
RUN echo "lregenar:lregenar" | chpasswd

RUN mkdir -p /var/ftp

COPY ./srcs/vsftpd.conf /etc/vsftpd/vsftpd.conf

COPY ./srcs/start.sh .

RUN chmod 755 start.sh

EXPOSE 20 21 30000

CMD ["sh", "start.sh"]
