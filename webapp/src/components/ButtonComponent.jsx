import Button from 'react-bootstrap/Button';
import React from 'react';
import axios from 'axios';


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
        return <Button variant = "primary" size = "lg" onClick = { this.sendPacket }>{this.id}</Button>
    }
}

export default ButtonComponent;