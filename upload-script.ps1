try
{
    taskkill /IM python3.exe /F
    if($?){
    Start-Sleep 3
    }
}
catch
{
    echo "No python process found."
}

pio run -t upload

Start-Sleep 3
netsh wlan connect name = "gonzyProject" ssid = "gonzyProject" interface = "Wi-Fi"

if ($?)
{
    for ($i = 0; $i -le 3; $i++){
        python3 ./Serial-monitor.py -m
        Start-Sleep 3
    }
}