var express = require("express");
var bodyParser = require("body-parser"); 
var cors = require("cors"); 
var app = express(); 


app.use(bodyParser.urlencoded({extended: false}));
app.use(express.json()); 
app.use(express.text()); 
app.use(cors()); 


app.post('/postVals', (req,res)=>
{
    const temperature = req.body.temperature; 
    const humidity = req.body.humidity; 



    console.log(temperature);
    console.log(humidity);

    res.send(  
      {
        msg: "Values Successfully Sent"
      });    


}); 



app.get('/getVals', (req,res)=>
{
    
    
    console.log("temp: ", {temperature});
    res.send(temperature);
})






// Data storage variable
let postData = null;

// POST route to receive data
app.post('/send-data', (req, res) => {
  // Assuming data is sent in the request body
  postData = req.body;
  res.send('Data received successfully!');
});

// GET route to display the received data
app.get('/display-data', (req, res) => {
  if (postData) {
    res.send(`Data received: ${JSON.stringify(postData)}`);
  } else {
    res.send('No data received yet.');
  }
});



let tempData = null; 

app.post('/send-data-ESP32', (req,res) =>
{
    tempData = req.body; 

    console.log("Received Data: ", {tempData});
    res.sendStatus(200);
});




app.post('/send-data-ESP32', (req,res) =>
{
    tempData = req.body; 

    console.log(tempData);
   1 

    res.send({
        msg: "Data Sent Successfully"
    });
});


app.get('/get-data-ESP32', (req,res)=>
{

    if(tempData)
    {
        res.send(tempData);
    }
    else
    {
        res.send(null);
    }
});








app.listen(3000, ()=>
{
    console.log("Listening to port 3000"); 
})