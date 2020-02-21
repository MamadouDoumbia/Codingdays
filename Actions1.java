/*
 * LoadRunner Java script. (Build: 3020)
 * 
 * Script Description: 
 *                     
 */

import lrapi.lr;

import org.apache.avro.Schema;
import org.apache.avro.generic.GenericData;
import org.apache.avro.generic.GenericRecord;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.clients.producer.ProducerRecord;
import java.util.Properties;


public class Actions
{

	public int init() throws Throwable {
		return 0;
	}//end of init


	public int action() throws Throwable {

String topic = "topic1";
//String topic = "test-avro6";

Properties props = new Properties();
props.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
props.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG,
          io.confluent.kafka.serializers.KafkaAvroSerializer.class);
props.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG,
          io.confluent.kafka.serializers.KafkaAvroSerializer.class);
props.put("schema.registry.url", "http://localhost:8081");
KafkaProducer producer = new KafkaProducer(props);

//String key = "key1";
//String userSchema = "{\"type\":\"record\"," +
//                    "\"name\":\"myrecord\"," +
//                    "\"fields\":[{\"name\":\"f1\",\"type\":\"string\"}]}";
                    
String userSchema = "{"+
     "\"type\": \"record\","+
     "\"namespace\": \"com.example\","+
     "\"name\": \"Customer\","+
     "\"version\": \"1\","+
     "\"fields\": ["+
       "{ \"name\": \"first_name\", \"type\": \"string\", \"doc\": \"First Name of Customer\" },"+  
       "{ \"name\": \"last_name\", \"type\": \"string\", \"doc\": \"Last Name of Customer\" },"+  
       "{ \"name\": \"age\", \"type\": \"int\", \"doc\": \"Age at the time of registration\" },"+  
       "{ \"name\": \"height\", \"type\": \"float\", \"doc\": \"Height at the time of registration in cm\" },"+  
       "{ \"name\": \"weight\", \"type\": \"float\", \"doc\": \"Weight at the time of registration in kg\" },"+
       "{ \"name\": \"automated_email\", \"type\": \"boolean\", \"default\": true, \"doc\": \"Field indicating if the user is enrolled in marketing emails\" }"+
     "]"+
"}";
	
Schema.Parser parser = new Schema.Parser();
Schema schema = parser.parse(userSchema);
GenericRecord avroRecord = new GenericData.Record(schema);
//avroRecord.put("f1", "value1");

avroRecord.put("first_name", "John");
avroRecord.put("last_name", "Doe");
avroRecord.put("age", 26);
avroRecord.put("height", 175f);
avroRecord.put("weight", 70.5f);
avroRecord.put("automated_email", false);

System.out.println("Mon Msg avro est :"+ avroRecord);


//ProducerRecord<Object, Object> record = new ProducerRecord<>(topic, key, avroRecord);
ProducerRecord<Object, Object> record = new ProducerRecord<>(topic, avroRecord);

System.out.println("Mon Msg record est :"+ record);
producer.send(record);
  producer.flush();
  producer.close();
//
//try {
//  producer.send(record);
//} catch(SerializationException e) {
//  // may need to do something with it
//}
//// When you're finished producing records, you can flush the producer to ensure it has all been written to Kafka and
//// then close the producer to free its resources.
//finally {
//  producer.flush();
//  producer.close();
//}
		return 0;
	}//end of action


	public int end() throws Throwable {
		return 0;
	}//end of end
}
