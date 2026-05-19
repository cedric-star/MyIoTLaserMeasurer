#!/run/current-system/sw/bin/python3

import csv
import sys
from datetime import datetime
def convert_influx_csv(input_file, output_file):
    
    with open(input_file, 'r', encoding='utf-8') as infile, open(output_file, 'w', newline='', encoding='utf-8') as outfile:
        
        reader = csv.reader(infile)
        
        # Erste 2 Header-Zeilen überspringen (InfluxDB-Metadaten)
        next(reader)  # #group Zeile
        next(reader)  # #datatype Zeile
        next(reader)  # #default Zeile
        
        # Eigentliche CSV-Header lesen
        headers = next(reader)
        
        # Writer für sauberes CSV
        writer = csv.writer(outfile)
        writer.writerow(['Zeit', 'Messwert', 'Wert', 'Sensor', 'Standort'])
        
        # Daten verarbeiten
        for row in reader:
            if len(row) >= len(headers):
                # Indizes der relevanten Spalten finden
                try:
                    time_idx = headers.index('_time')
                    field_idx = headers.index('_field')
                    value_idx = headers.index('_value')
                    sensor_idx = headers.index('sensor')
                    standort_idx = headers.index('standort')
                    
                    zeit = row[time_idx]
                    # Zeit formatieren (optional: von ISO auf lesbares Format)
                    try:
                        dt_utc = datetime.fromisoformat(zeit.replace('Z', '+00:00'))
                        dt_local = dt_utc.astimezone()
                        zeit_formatiert = dt_local.strftime('%Y-%m-%d %H:%M:%S')
                    except:
                        zeit_formatiert = zeit
                    
                    messwert = row[field_idx]
                    wert = row[value_idx]
                    sensor = row[sensor_idx] if sensor_idx < len(row) else ''
                    standort = row[standort_idx] if standort_idx < len(row) else ''
                    
                    # Nur Zeilen mit tatsächlichen Werten (nicht-leer) schreiben
                    if wert and wert.strip():
                        wert = round(float(wert))
                        writer.writerow([zeit_formatiert, messwert, wert, sensor, standort])
                        
                except ValueError as e:
                    print(f"Warnung: Konnte Spalten nicht finden - {e}")
                    continue


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Verwendung: python3 convert_influx_csv.py <input.csv> [output.csv]")
        print("Option: --pivot für pivotierte Ansicht (PM1,PM2.5,PM10 pro Zeit)")
        sys.exit(1)
    
    input_file = sys.argv[1]

    # Standard: lange Format
    output_file = sys.argv[2] if len(sys.argv) > 2 else input_file.replace('.csv', '_clean.csv')
    convert_influx_csv(input_file, output_file)
    print(f"Bereinigt: {output_file}")