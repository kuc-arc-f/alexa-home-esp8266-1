import paho.mqtt.publish as publish
import sys
import logging
import time
import getopt
import traceback

mTopic="item-test/device-1/test1"
mMQTT_HostName="ec2-XX-XX-XXX-XX.compute-1.amazonaws.com"

def lambda_handler(event, context):
    print('# Lambda-handler')
    #proc_iotSender()
    access_token = event['payload']['accessToken']

    if event['header']['namespace'] == 'Alexa.ConnectedHome.Discovery':
        return handleDiscovery(context, event)

    elif event['header']['namespace'] == 'Alexa.ConnectedHome.Control':
        return handleControl(context, event)


#det proc_iotSender
def proc_iotSender( sPay ):
	try:
#		sPay="1"
		publish.single(topic=mTopic, payload=sPay, hostname=mMQTT_HostName , port=1883 )		
	except:
		print "--------------------------------------------"
		print traceback.format_exc(sys.exc_info()[2])
		print "--------------------------------------------"

def handleDiscovery(context, event):
    #proc_iotSender()
    payload = ''
    header = {
        "namespace": "Alexa.ConnectedHome.Discovery",
        "name": "DiscoverAppliancesResponse",
        "payloadVersion": "2"
        }

    if event['header']['name'] == 'DiscoverAppliancesRequest':
        payload = {
            "discoveredAppliances":[
                {
                    "applianceId":"device001",
                    "manufacturerName":"yourManufacturerName",
                    "modelName":"model 01",
                    "version":"your software version number here.",
                    "friendlyName":"Smart Home Virtual Device",
                    "friendlyDescription":"Virtual Device for the Sample Hello World Skill",
                    "isReachable":True,
                    "actions":[
                        "turnOn",
                        "turnOff"
                    ],
                    "additionalApplianceDetails":{
                        "extraDetail1":"optionalDetailForSkillAdapterToReferenceThisDevice",
                        "extraDetail2":"There can be multiple entries",
                        "extraDetail3":"but they should only be used for reference purposes.",
                        "extraDetail4":"This is not a suitable place to maintain current device state"
                    }
                }
            ]
        }
    return { 'header': header, 'payload': payload }

def handleControl(context, event):
    print('# control_device ')
    payload = ''
    device_id = event['payload']['appliance']['applianceId']
    message_id = event['header']['messageId']
    
    name=''
    if event['header']['name'] == 'TurnOnRequest':
    	print('#turn on ' + event['payload']['appliance']['applianceId'])
    	proc_iotSender("1")
        payload = { }
        name='TurnOnConfirmation'
        
    if event['header']['name'] == 'TurnOffRequest':
    	print('#turn off ' + event['payload']['appliance']['applianceId'])
    	proc_iotSender("0")
        payload = { }
        name='TurnOffConfirmation'

    header = {
        "namespace": event['header']['namespace'],
        "name": name,
        "payloadVersion": event['header']['payloadVersion'],
        "messageId": message_id
        }
        
#   header = {
#       "namespace":"Alexa.ConnectedHome.Control",
#       "name":"TurnOnConfirmation",
#       "payloadVersion":"2",
#       "messageId": message_id
#       }
    return { 'header': header, 'payload': payload }

