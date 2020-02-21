/*
 * LoadRunner Java script. (Build: 3020)
 * 
 * Script Description: 
 *                     
 */

import lrapi.lr;



import java.util.*;

import org.apache.avro.AvroRuntimeException;
import org.apache.avro.Schema;
import org.apache.avro.file.DataFileReader;
import org.apache.avro.file.DataFileWriter;
import org.apache.avro.generic.*;
import org.apache.avro.io.DatumReader;
import org.apache.avro.io.DatumWriter;



import java.util.Properties;

public class Actions
{

Schema.Parser parser = new Schema.Parser();
//        Schema schema = parser.parse("{\n" +
//                "     \"type\": \"record\",\n" +
//                "     \"namespace\": \"com.example\",\n" +
//                "     \"name\": \"Customer\",\n" +
//                "     \"fields\": [\n" +
//                "       { \"name\": \"first_name\", \"type\": \"string\", \"doc\": \"First Name of Customer\" },\n" +
//                "       { \"name\": \"last_name\", \"type\": \"string\", \"doc\": \"Last Name of Customer\" },\n" +
//                "       { \"name\": \"age\", \"type\": \"int\", \"doc\": \"Age at the time of registration\" },\n" +
//                "       { \"name\": \"height\", \"type\": \"float\", \"doc\": \"Height at the time of registration in cm\" },\n" +
//                "       { \"name\": \"weight\", \"type\": \"float\", \"doc\": \"Weight at the time of registration in kg\" },\n" +
//                "       { \"name\": \"automated_email\", \"type\": \"boolean\", \"default\": true, \"doc\": \"Field indicating if the user is enrolled in marketing emails\" }\n" +
//                "     ]\n" +
//                "}");
                
         
         Schema schema = parser.parse("{\n" +
                "     \"type\": \"record\",\n" +
                "     \"namespace\": \"com.example\",\n" +
                "     \"name\": \"Customer\",\n" +
                "     \"fields\": [\n" +
                "       { \"name\": \"first_name\", \"type\": \"string\", \"default\": \"Mamadou\", \"doc\": \"First Name of Customer\" },\n" +
                "       { \"name\": \"last_name\", \"type\": \"string\", \"default\": \"Doumbia\", \"doc\": \"Last Name of Customer\" },\n" +
                "       { \"name\": \"age\", \"type\": \"string\", \"default\": \"20\", \"doc\": \"Age at the time of registration\" },\n" +
                "       { \"name\": \"height\", \"type\": \"string\", \"default\": \"1,80\", \"doc\": \"Height at the time of registration in cm\" },\n" +
                "       { \"name\": \"weight\", \"type\": \"string\", \"default\": \"70\", \"doc\": \"Weight at the time of registration in kg\" },\n" +
                "       { \"name\": \"automated_email\", \"type\": \"string\", \"default\": \"mdo\", \"doc\": \"Field indicating if the user is enrolled in marketing emails\" }\n" +
                "     ]\n" +
                "}");


        // we build our first customer
        GenericRecordBuilder customerBuilder = new GenericRecordBuilder(schema);
//        lr2.fieldSetter(customerBuilder, "type1", "John");
//        customerBuilder.set("first_name", "John");
//        customerBuilder.set("last_name", "Doe");
//        customerBuilder.set("age", 26);
//        customerBuilder.set("height", 175f);
//        customerBuilder.set("weight", 70.5f);
//        customerBuilder.set("automated_email", false);
        GenericData.Record myCustomer = customerBuilder.build();
//        System.out.println(myCustomer);

	  
//	  lr2.fieldSetter(customerBuilder, "first_name", "John");
//        customerBuilder.set("first_name", "John");
//        customerBuilder.set("last_name", "Doe");
//        customerBuilder.set("age", 26);
//        customerBuilder.set("height", 175f);
//        customerBuilder.set("weight", 70.5f);
//        customerBuilder.set("automated_email", false);
//        GenericData.Record myCustomer = customerBuilder.build();
//        System.out.println(myCustomer);
        
        
//	GenericData.Record a = avroRecord.build();
	public int init() throws Throwable {
		return 0;
	}//end of init


	public int action() throws Throwable {
		System.out.println(myCustomer);
		return 0;
	}//end of action


	public int end() throws Throwable {
		return 0;
	}//end of end
}
