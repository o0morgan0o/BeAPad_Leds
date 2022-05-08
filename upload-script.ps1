
try{

    taskkill /IM python3.exe /F
}catch{
    echo "No python process found."
}

pio run -t upload
if($?){
    python3 ./Serial-monitor.py -m
}