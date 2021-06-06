import {Button} from 'react-bootstrap';
import React from 'react';
import axios from 'axios';
import './ButtonComponent.css';

class ResetSwitchComponent extends React.Component {

    sendPacket = () => {
        const url = `http://localhost:8081/switch`
        axios.post(url, {id: 0})
        .then(function (response) {
            console.log(response.data);
        })
        .catch(function (error) {
            console.log(error);
        });
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant="dark" size="lg" onClick={this.sendPacket}>Reset</Button>
        </div>
    }
}

export default ResetSwitchComponent;