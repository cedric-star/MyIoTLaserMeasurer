# Node-Red
- command: node-red (nodered installieren vorher)
- "Palette verwalten" → Tab "Installieren". Suche nach node-red-contrib-aedes

# ablauf morgen
## starten
- handy wlan anmachen
- handy an laptop anschließen
- laptop mit handywlan anschließen
- node-red starten: 
    - node-red
    - http://127.0.0.1:1880/dashboard/page1
- influx db starten:
    - docker compose up influxdb
    - http://localhost:8086
- wio an laptop anschließen
## beenden
- in influxdb weboberfläche:
    - from bucket luftqualitaet
    - filter: luftqualitaet
    - rechts auf submit
    - download csv