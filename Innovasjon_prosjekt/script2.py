import time
from selenium import webdriver

from datetime import datetime, timedelta
rom_1_tid = ""
rom_2_tid = ""
rom_3_tid = ""
rom_4_tid = ""
url = "file:///home/thomas/elsys/grunnkurs/Innovasjon_prosjekt/index.html"
waiting_duration_before_refresh = 5

driver = webdriver.Firefox()
driver.get(url)

def read_file():
    with open("room.txt", "r") as f:
        SMRF1 = f.readlines()
    return SMRF1

def get_time(hour, minute, second):
    currentDateAndTime = datetime.now()
    
    currentTime = currentDateAndTime.strftime("%H:%M:%S")
    currentTime = datetime.strptime(currentTime, "%H:%M:%S")
    
    data_time = hour +":"+ minute +":"+ second

    data_time = datetime.strptime(data_time, "%H:%M:%S")
    data_time = data_time + timedelta(minutes=30)
    delta = data_time - currentTime
    if (delta.days < 0):
        return '00:00:00'
    
    return delta

def delta_to_time(delta):
    time_obj = datetime.strptime(str(delta),'%H:%M:%S').time()
    return time_obj

def update_html():
    rom_1_tid = ""
    rom_2_tid = ""
    rom_3_tid = ""
    rom_4_tid = ""
    arr = []
    with open('room.txt') as f:
        for row in f:
            
            arr.append(row.replace('\n','').split(','))
    for element in arr:
        if element[0] == "1":
            rom_1_tid = delta_to_time(get_time(element[1], element[2], element[3])).strftime('%H:%M:%S')
        elif element[0] == "2":
            rom_2_tid = delta_to_time(get_time(element[1], element[2], element[3])).strftime('%H:%M:%S')
        elif element[0] == "3":
            rom_3_tid = delta_to_time(get_time(element[1], element[2], element[3])).strftime('%H:%M:%S')
        elif element[0] == "4":
            rom_4_tid = delta_to_time((get_time(element[1], element[2], element[3]))).strftime('%H:%M:%S')
    
    
    html = html_changes(rom_1_tid, rom_2_tid, rom_3_tid, rom_4_tid)
    index =  open("index.html", "w")
    index.write(html)
    
    # Make a way to refreshe webpages opened



def html_changes(rom_1_tid,rom_2_tid,rom_3_tid,rom_4_tid):
    print([rom_1_tid, rom_2_tid, rom_3_tid, rom_4_tid])

    html = """
    <!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="styles.css">
    <script src="scripts.js" defer></script>
    <title>Rom og tid</title>
  </head>

<body>
  <div id="table_header"> Rom oversikt</div>
  <div id="table_container">
    <table>
      <tr>
        <th>Rom</th>
        <th>Tid</th>
        <th>Fase</th>
      </tr>
      <tr>
        <td>1</td>
        <td><div id="rom1">{first}</div></td>
        <td>Vent</td>
      </tr>
      <tr>
        <td>2</td>
        <td><div id="rom2">{second}</div></td>
        <td>Drikke</td>
      </tr>
      <tr>
        <td>3</td>
        <td><div id="rom3">{third}</div></td>
        <td>Drikke</td>
      </tr>
      <tr>
        <td>4</td>
        <td><div id="rom4">{fourth}</div></td>
        <td>Drikke</td>
      </tr>
    </table>  
  </div>
</body>
</html>
    """.format(first=rom_1_tid, second= rom_2_tid, third= rom_3_tid, fourth = rom_4_tid)
    return html
        


initial = read_file()
while True:
    current = read_file()
    if initial != current:
        # for line in current:
        #     if line not in initial:
        #         print(line)
        # initial = current
        # Run another function
        update_html()
        driver.refresh()
        initial = read_file()


    time.sleep(1)


