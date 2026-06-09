#!/run/current-system/sw/bin/python3

import sys

import pandas as pd
import plotly.graph_objects as go

if len(sys.argv) < 2:
    print("Verwendung: python plot_messwerte.py <datei.csv>")
    sys.exit(1)

df = pd.read_csv(sys.argv[1], parse_dates=["Zeit"])

fig = go.Figure()
for name, gruppe in df.groupby("Messwert"):
    fig.add_trace(
        go.Scatter(x=gruppe["Zeit"], y=gruppe["Wert"], mode="lines+markers", name=name)
    )

fig.update_layout(title="Messwerte über Zeit", xaxis_title="Zeit", yaxis_title="Wert")

fig.show()
