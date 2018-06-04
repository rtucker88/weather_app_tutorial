let component = ReasonReact.statelessComponent("LoadingDisplay");

let make = (_children) => {
  ...component,
  render: self =>
    <div className='loading'>
            <img className='loadingIcon' src={LoadingIcon} alt='loading icon'/>
          </div>,
};
