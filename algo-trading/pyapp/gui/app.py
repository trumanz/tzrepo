import panel as pn
import numpy as np
import matplotlib.pyplot as plt  # Import Matplotlib

pn.extension()


import pandas as pd
import sqlalchemy

# Function to connect to the database and fetch data
def get_data():
    # Create the database engine
    engine = sqlalchemy.create_engine('postgresql://qa:qa@localhost:5432/qa')
    
    # Use a context manager to handle the connection automatically
    with engine.connect() as connection:
        # Query the data (e.g., counting rows in a table)
        df = pd.read_sql_query("SELECT COUNT(*) as count FROM bid_ask_data", connection)
    
    # The connection is automatically closed when the block exits
    return df

# Fetch the data
data = get_data()

# Display the result
print(data)



# Create a markdown pane to show the result
markdown_pane = pn.pane.Markdown(f"## Count of values in `my_table`: {data['count'].iloc[0]}")

# Display the markdown pane in the notebook
markdown_pane


# Function to update the count, accepting an optional event parameter
def update_count(event=None):
    data = get_data()
    return f"## Count of values in `bid_ask_data`: {data['count'].iloc[0]}"

# Create a button to refresh the count
button = pn.widgets.Button(name='Refresh Count', button_type='primary')

# Create a dynamic markdown pane that updates when the button is clicked
dynamic_pane = pn.bind(update_count, button)

# Create a layout with the button and dynamic markdown
layout = pn.Column(button, dynamic_pane)

# Display the layout
layout.servable()