let component = ReasonReact.statelessComponent("Home");

let make = (_children) => {
  ...component,
  render: _self =>
       <div>
        <div className='header'>
          <h2>(ReactReason.ReactString("Weather Forecast"))</h2>
          <img src={LightningBolt}/>
        </div>
        <div className="instructions">
          <p>(ReactReason.ReactString("Enter a US zipcode below to get the current weather conditions for that area.")</p>
        </div>
        <div className='zipcodeInput'>
          <form method='POST' action='/search-location'>
            <input type='text' placeholder='Enter zipcode..' name='zipcode'/>
            <button>(ReactReason.ReactString("ENTER"))</button>
          </form>
        </div>
      </div>,
};
