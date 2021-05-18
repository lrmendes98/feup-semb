import {Button} from 'react-bootstrap';
import React from 'react';
import axios from 'axios';
import './ButtonComponent.css';

class SwitchComponent extends React.Component {
    constructor(props) {
        super(props)
        this.id = props.id;
    }

    sendPacket = () => {
        const url = `http://localhost:8081/switch`
        axios.post(url, {id: this.id})
        .then(function (response) {
            console.log(response.data);
        })
        .catch(function (error) {
            console.log(error);
        });
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant="dark" size="lg" onClick={this.sendPacket}>Switch {this.id}</Button>
        </div>
    }
}

export default SwitchComponent;