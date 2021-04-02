srcs=./srcs

services=(		\
 	nginx		\
	mysql		\
	phpmyadmin	\
	wordpress	\
	ftps		\
	telegraf	\
	influxdb	\
	grafana		\
)

minikube start --driver=virtualbox
minikube addons enable metallb

eval $(minikube docker-env)
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/namespace.yaml
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/metallb.yaml
kubectl create secret generic -n metallb-system memberlist --from-literal=secretkey="$(openssl rand -base64 128)"
kubectl apply -f ./srcs/metallb/metallb.yaml

echo "Pre-config done"

echo "Building images:"
for service in "${services[@]}"
do
	echo "$service:"
	echo "	Building new image..."		
	docker build -t $service $srcs/$service > /dev/null
	echo "	Creating container..."
	kubectl apply -f srcs/$service-deployment.yaml > /dev/null
	if [[ $service == "influxdb" ]]
	then
		echo "	Additional things for influxdb"
		kubectl apply -f ./srcs/influxdb/srcs/influxdb-conf.yaml > /dev/null
		kubectl apply -f ./srcs/influxdb/srcs/volume.yaml > /dev/null
		kubectl apply -f ./srcs/influxdb/srcs/vol_d.yaml > /dev/null
	fi
	echo "done!"
done 

echo "ft_services just 5 more seconds"
sleep 15
echo "ft_services deployment done"

kubectl get svc
kubectl get pods

minikube dashboard & >/dev/null

echo "

Username & password information:
lregenar:lregenar
wordpress:
			lregenar:lregenar (Admin)
			guest:guest (Subscriber)				
			author:author (Author)
			visitor:visitor (Subscriber)

Ports:
3000		grafana
5000		phpmyadmin
5050		wordpress

TEST 
curl -I http://192.168.99.101
# kubectl exec deploy/nginx -- pkill sshd ; kubectl exec deploy/ftps -- pkill vsftpd ; kubectl exec deploy/grafana -- pkill grafana ; kubectl exec deploy/telegraf -- pkill telegraf ; kubectl exec deploy/mysql -- pkill mysqld ; kubectl exec deploy/influxdb -- pkill influxd ; kubectl exec deploy/nginx -- pkill nginx
"
