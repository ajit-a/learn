#include<json/json.h>
#include<stdio.h>

int main()
{
	char *string = "{\"name\" : \"Ajit\",\"tags\" : [ \"c\" , \"c++\", \"java\", \"PHP\" ], \"author-details\": { \"name\" : \"Joys of Programming\", \"Number of Posts\" : 10 } }";
	json_object *jobj = json_tokener_parse(string);
	json_type type = json_object_get_type(jobj);


	json_object_object_foreach(jobj, key, val) 
	{
		printf("type: ",type);
		type = json_object_get_type(val);
		switch (type) 
		{
			case json_type_null: printf("json_type_null\n");
			break;
			case json_type_boolean: printf("json_type_boolean\n");
			break;
			case json_type_double: printf("json_type_double\n");
			break;
			case json_type_int: printf("json_type_int\n");
			break;
			case json_type_object: printf("json_type_object\n");
			break;
			case json_type_array:{ printf("json_type_array\n");
				jobj=json_object_object_get(jobj,key);
				int arraylen=json_object_array_length(jobj);
				json_object *jo;
				for(int i;i<arraylen;i++)
				{
					jo=json_object_array_get_idx(jobj,i);
					printf("%s\n",json_object_get_string(jo));
				}}
			break;
			case json_type_string: printf("json_type_string\n");
			break;
		}
	}

	return 0;
}
