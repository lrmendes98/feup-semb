import Button from 'react-bootstrap/Button';
import axios from 'axios';
import './App.css';

function sendPacket() {
  axios.get('http://localhost:8081/')
    .then(function (response) {
      console.log(response);
    })
    .catch(function (error) {
      console.log(error);
    });
}

function App() {
  return (
    <div className="App">
      <Button onClick={sendPacket()} variant="primary">Send Packet</Button>
    </div>
  );
}

export default App;
