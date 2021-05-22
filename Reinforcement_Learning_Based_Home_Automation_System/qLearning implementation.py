import numpy as np
import mysql.connector

episodes = 15000
learningFactor = 0.6
discount = 0.8
epsilon = 0.4
oldState = [0,0,0,0,0,0,0,0,0,0,0,0]

def calculateReward (RewardTable, deviceData, deviceIndex):
    for onOffTime in deviceData:
        converted2Integer = int(''.join(map(str,onOffTime)))
        index4Reward = ( ( ( converted2Integer // 100 ) * 60 ) + ( converted2Integer % 100 ) )
        rewards[deviceIndex,index4Reward] += 1

mySQL_select_L1_ON_query = "select triggerTime from appliances where Device = 'L1' and DevStatus = 'ON'"
mySQL_select_L1_OFF_query = "select triggerTime from appliances where Device = 'L1' and DevStatus = 'OFF'"
mySQL_select_L2_ON_query = "select triggerTime from appliances where Device = 'L2' and DevStatus = 'ON'"
mySQL_select_L2_OFF_query = "select triggerTime from appliances where Device = 'L2' and DevStatus = 'OFF'"
mySQL_select_L3_ON_query = "select triggerTime from appliances where Device = 'L3' and DevStatus = 'ON'"
mySQL_select_L3_OFF_query = "select triggerTime from appliances where Device = 'L3' and DevStatus = 'OFF'"
mySQL_select_L4_ON_query = "select triggerTime from appliances where Device = 'L4' and DevStatus = 'ON'"
mySQL_select_L4_OFF_query = "select triggerTime from appliances where Device = 'L4' and DevStatus = 'OFF'"
mySQL_select_F1_ON_query = "select triggerTime from appliances where Device = 'F1' and DevStatus = 'ON'"
mySQL_select_F1_OFF_query = "select triggerTime from appliances where Device = 'F1' and DevStatus = 'OFF'"
mySQL_select_F2_ON_query = "select triggerTime from appliances where Device = 'F2' and DevStatus = 'ON'"
mySQL_select_F2_OFF_query = "select triggerTime from appliances where Device = 'F2' and DevStatus = 'OFF'"

try:
    print("Establishing Connection to MySQL")
    connection = mysql.connector.connect(host = 'localhost',
                                         database = 'mockdatabase',
                                         user = 'root',
                                         password = 'root')
    print("Fetching data from appliances table")
    cursor = connection.cursor(buffered=True)
    
    cursor.execute(mySQL_select_L1_ON_query)
    L1OnData = cursor.fetchall()
    cursor.execute(mySQL_select_L1_OFF_query)
    L1OffData = cursor.fetchall()
    cursor.execute(mySQL_select_L2_ON_query)
    L2OnData = cursor.fetchall()
    cursor.execute(mySQL_select_L2_OFF_query)
    L2OffData = cursor.fetchall()
    cursor.execute(mySQL_select_L3_ON_query)
    L3OnData = cursor.fetchall()
    cursor.execute(mySQL_select_L3_OFF_query)
    L3OffData = cursor.fetchall()
    cursor.execute(mySQL_select_L4_ON_query)
    L4OnData = cursor.fetchall()
    cursor.execute(mySQL_select_L4_OFF_query)
    L4OffData = cursor.fetchall()
    cursor.execute(mySQL_select_F1_ON_query)
    F1OnData = cursor.fetchall()
    cursor.execute(mySQL_select_F1_OFF_query)
    F1OffData = cursor.fetchall()
    cursor.execute(mySQL_select_F2_ON_query)
    F2OnData = cursor.fetchall()
    cursor.execute(mySQL_select_F2_ON_query)
    F2OnData = cursor.fetchall()
    cursor.execute(mySQL_select_F2_ON_query)
    F2OffData = cursor.fetchall()

except Error as e:
    print("Error Establishing COnnection to MySQL")

finally:
    if (connection.is_connected()):
        cursor.close()
        connection.close()
        print("Connection is closed")

qTable = np.zeros((12,1440))

states = []

for i in range(1440):
    states.append(i)

rewards = np.zeros((12,1440))

calculateReward(rewards,L1OnData,0)
calculateReward(rewards,L1OffData,1)
calculateReward(rewards,L2OnData,2)
calculateReward(rewards,L2OffData,3)
calculateReward(rewards,L3OnData,4)
calculateReward(rewards,L3OffData,5)
calculateReward(rewards,L4OnData,6)
calculateReward(rewards,L4OffData,7)
calculateReward(rewards,F1OnData,8)
calculateReward(rewards,F1OffData,9)
calculateReward(rewards,F2OnData,10)
calculateReward(rewards,F2OffData,11)

currentState = [int(''.join(map(str,L1OnData[-1]))),
                int(''.join(map(str,L1OffData[-1]))),
                int(''.join(map(str,L2OnData[-1]))),
                int(''.join(map(str,L2OffData[-1]))),
                int(''.join(map(str,L3OnData[-1]))),
                int(''.join(map(str,L3OffData[-1]))),
                int(''.join(map(str,L4OnData[-1]))),
                int(''.join(map(str,L4OffData[-1]))),
                int(''.join(map(str,F1OnData[-1]))),
                int(''.join(map(str,F1OffData[-1]))),
                int(''.join(map(str,F2OnData[-1]))),
                int(''.join(map(str,F2OffData[-1])))]

for deviceIndex in range(12):
    oldState[deviceIndex] = ( ((currentState[deviceIndex] // 100) * 60) + (currentState[deviceIndex] % 100) )

for episode in range(episodes):
    for i in range(6):
        action = np.random.randint(2)
        deviceIndex = (2*i+action)
        
        if np.random.random() < epsilon:
            newState = np.argmax(qTable[(2*i)+action])
        else:
            newState = states[np.random.randint(1440)]
        
        TD = (rewards[deviceIndex,newState] + (discount * qTable[deviceIndex,newState])) - qTable[deviceIndex,oldState[deviceIndex]]
        qTable[deviceIndex,newState] = qTable[deviceIndex,oldState[deviceIndex]] + (learningFactor * TD)
        oldState[deviceIndex] = newState

L1OnTime = int(np.argmax(qTable[0]))
L1OffTime = int(np.argmax(qTable[1]))
L2OnTime = int(np.argmax(qTable[2]))
L2OffTime = int(np.argmax(qTable[3]))
L3OnTime = int(np.argmax(qTable[4]))
L3OffTime = int(np.argmax(qTable[5]))
L4OnTime = int(np.argmax(qTable[6]))
L4OffTime = int(np.argmax(qTable[7]))
F1OnTime = int(np.argmax(qTable[8]))
F1OffTime = int(np.argmax(qTable[9]))
F2OnTime = int(np.argmax(qTable[10]))
F2OffTime = int(np.argmax(qTable[11]))

L1OnTime = ( ((L1OnTime // 60) * 100) + (L1OnTime % 60) )
L1OffTime = ( ((L1OffTime // 60) * 100) + (L1OffTime % 60) )
L2OnTime = ( ((L2OnTime // 60) * 100) + (L2OnTime % 60) )
L2OffTime = ( ((L2OffTime // 60) * 100) + (L2OffTime % 60) )
L3OnTime = ( ((L3OnTime // 60) * 100) + (L3OnTime % 60) )
L3OffTime = ( ((L3OffTime // 60) * 100) + (L3OffTime % 60) )
L4OnTime = ( ((L4OnTime // 60) * 100) + (L4OnTime % 60) )
L4OffTime = ( ((L4OffTime // 60) * 100) + (L4OffTime % 60) )
F1OnTime = ( ((F1OnTime // 60) * 100) + (F1OnTime % 60) )
F1OffTime = ( ((F1OffTime // 60) * 100) + (F1OffTime % 60) )
F2OnTime = ( ((F2OnTime // 60) * 100) + (F2OnTime % 60) )
F2OffTime = ( ((F2OffTime // 60) * 100) + (F2OffTime % 60) )

try:
    print("Establishing Connection to MySQL")
    connection = mysql.connector.connect(host = 'localhost',
                                         database = 'mockdatabase',
                                         user = 'root',
                                         password = 'root')

    cursor = connection.cursor()

    print("Updating learneddata table")

    cursor.execute("UPDATE learneddata SET DeviceName = 'L1', onOffTime = "+str(L1OnTime)+" WHERE Sr = 1")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L1', onOffTime = "+str(L1OffTime)+" WHERE Sr = 2")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L2', onOffTime = "+str(L2OnTime)+" WHERE Sr = 3")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L2', onOffTime = "+str(L2OffTime)+" WHERE Sr = 4")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L3', onOffTime = "+str(L3OnTime)+" WHERE Sr = 5")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L3', onOffTime = "+str(L3OffTime)+" WHERE Sr = 6")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L4', onOffTime = "+str(L4OnTime)+" WHERE Sr = 7")
    cursor.execute("UPDATE learneddata SET DeviceName = 'L4', onOffTime = "+str(L4OffTime)+" WHERE Sr = 8")
    cursor.execute("UPDATE learneddata SET DeviceName = 'F1', onOffTime = "+str(F1OnTime)+" WHERE Sr = 9")
    cursor.execute("UPDATE learneddata SET DeviceName = 'F1', onOffTime = "+str(F1OffTime)+" WHERE Sr = 10")
    cursor.execute("UPDATE learneddata SET DeviceName = 'F2', onOffTime = "+str(F2OnTime)+" WHERE Sr = 11")
    cursor.execute("UPDATE learneddata SET DeviceName = 'F2', onOffTime = "+str(F2OffTime)+" WHERE Sr = 12")
    
    connection.commit()

except Error as e:
    print("Error Establishing COnnection to MySQL")

finally:
    if (connection.is_connected()):
        cursor.close()
        connection.close()
        print("Connection is closed")
