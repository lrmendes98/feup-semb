import {Button, Alert} from 'react-bootstrap';
import React from 'react';
import axios from 'axios';
import './ButtonComponent.css';

class ButtonComponent extends React.Component {
    constructor(props) {
        super(props)
        this.id = props.id;
        this.state = {
            clicked: false
        }
    }

    sendPacket = () => {
        this.setState({ clicked: !this.state.clicked });
        const url = `http://localhost:8081/switch/${this.id}`
        axios.get(url)
            .then(function (response) {
                console.log(response.data);
            })
            .catch(function (error) {
                console.log(error);
            });
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant={this.state.clicked ? "success" : "dark"} size="lg" onClick={this.sendPacket}>Switch {this.id}</Button>
        </div>
    }
}

export default ButtonComponent;