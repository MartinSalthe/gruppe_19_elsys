from datetime import datetime, timedelta

# start time
start_time = "2:13:57"
end_time = "00:30:00"

# convert time string to datetime
t1 = datetime.strptime(start_time, "%H:%M:%S")
print(t1)
print('Start time:', t1.time())

t2 = datetime.strptime(end_time, "%H:%M:%S")
print('End time:', t2.time())

# get difference
delta = t2 + timedelta(minutes=30)
delta = t1-t2
print(delta)
# time difference in seconds

# time difference in milliseconds

