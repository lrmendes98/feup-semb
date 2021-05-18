import {Button} from 'react-bootstrap';
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
        const url = `http://localhost:8081/switch`
        axios.post(url, {id: this.id, state: !this.state.clicked})
        .then(function (response) {
            console.log(response.data);
        })
        .catch(function (error) {
            console.log(error);
        });
        this.setState({ clicked: !this.state.clicked });
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant={this.state.clicked ? "success" : "dark"} size="lg" onClick={this.sendPacket}>Switch {this.id}</Button>
        </div>
    }
}

export default ButtonComponent;